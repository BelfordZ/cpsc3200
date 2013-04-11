#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long long gcd(long long a, long long b, long long *s, long long *t)
{
  long long r, r1, r2, a1, a2, b1, b2, q;
  long long A = a;
  long long B = b;
 
  a1 = b2 = 1;
  a2 = b1 = 0;
 
  while (b) {
    assert(a1*A + a2*B == a);
    q = a / b;
    r = a % b;
    r1 = a1 - q*b1;
    r2 = a2 - q*b2;
    a = b;
    a1 = b1;
    a2 = b2;
    b = r;
    b1 = r1;
    b2 = r2;
  }
 
  *s = a1;
  *t = a2;
  assert(a >= 0);
  return a;
}

long long cra(long long n, long long *m, long long *a)
{
  long long x, i, k, prod, temp;
  long long gamma[2], v[2];

  /* compute inverses */
  for (k = 1; k < n; k++) {
    prod = m[0] % m[k];
    for (i = 1; i < k; i++) {
      prod = (prod * m[i]) % m[k];
    }
    gcd(prod, m[k], gamma+k, &temp);
    gamma[k] %= m[k];
    if (gamma[k] < 0) {
      gamma[k] += m[k];
    }
  }

  /* compute coefficients */
  v[0] = a[0];
  for (k = 1; k < n; k++) {
    temp = v[k-1];
    for (i = k-2; i >= 0; i--) {
      temp = (temp * m[i] + v[i]) % m[k];
      if (temp < 0) {
        temp += m[k];
      }
    }
    v[k] = ((a[k] - temp) * gamma[k]) % m[k];
    if (v[k] < 0) {
      v[k] += m[k];
    }
  }

  /* convert from mixed-radix representation */
  x = v[n-1];
  for (k = n-2; k >= 0; k--) {
    x = x * m[k] + v[k];
  }

  return x;
}

long long fast_exp(int b, int n)
{
  long long res = 1;
  long long x = b;

  while (n > 0) {
    if (n & 0x01) {
      n--;
      res *= x;
    } else {
      n >>= 1;
      x *= x;
    }
  }

  return res;
}

long long fast_exp_mod(int b, int n, int m)
{
  long long res = 1;
  long long x = b % m;

  while (n > 0) {
    if (n & 0x01) {
      n--;
      res *= x;
      res %= m;
    } else {
      n >>= 1;
      x *= x;
      x %= m;
    }
  }

  return res;
}

int factor(int n, int *factors)
{
  int count = 0;
  int p;

  while (n % 2 == 0) {
    n /= 2;
    factors[count++] = 2;
  }
  
  for (p = 3; p*p <= n; p += 2) {
    while (n % p == 0) {
      n /= p;
      factors[count++] = p;
    }
  }
  if (n > 1) {
    factors[count++] = n;
  }
  return count;
}

int phi(int count, int *factors)
{
  int val = 1;
  int i, j;

  for (i = 0; i < count; i = j) {
    for (j = i; j < count && factors[j] == factors[i]; j++)
      ;
    val *= fast_exp(factors[i], j-i-1) * (factors[i]-1);
  }
  return val;
}

int compute_plain(int b, int i, int bound)
{
  int prev, ans, k;

  if (!i) {
    return 1;
  }

  if ((prev = compute_plain(b, i-1, bound)) < 0) {
    return -1;
  }
 
  ans = 1;
  for (k = 0; k < prev; k++) {
    ans *= b;
    if (ans >= bound) {
      return -1;
    }
  }
  return ans;
}

int compute_mod(int b, int i, int m)
{
  int prev, k;
  int factors[32], count;
  long long mod[2], x[2];


  if (!i) {
    return 1;
  }
  if (m == 1) {
    return 0;
  }
  if (m == 2) {
    return b % 2;
  }
  if (b % m == 0) {
    return 0;
  }

  count = factor(m, factors);
  if (count == 1) {
    /* m is prime, easy case */
    prev = compute_mod(b, i-1, phi(count, factors));
    return fast_exp_mod(b, prev, m);
  } else if (factors[0] == factors[count-1]) {
    /* prime power case */
    if (b % factors[0]) {
      /* relatively prime, just do the above */
      prev = compute_mod(b, i-1, phi(count, factors));
      return fast_exp_mod(b, prev, m);
    } else {
      prev = compute_plain(b, i-1, count+1);
      if (prev < 0) {
	/* exponent too big, so result is 0 */
	return 0;
      }

      /* just do it: the exponent is small */
      return fast_exp_mod(b, prev, m);
    }
  } else {
    /* mixed primes, do Chinese remaindering */
    mod[0] = 1;
    for (k = 0; k < count && factors[k] == factors[0]; k++) {
      mod[0] *= factors[k];
    }
    mod[1] = m / mod[0];
    x[0] = compute_mod(b, i, mod[0]);
    x[1] = compute_mod(b, i, mod[1]);
    return cra(2, mod, x);
  }
}

int main(void)
{
  int n, b, i, bound;
  FILE *in, *out;

  if (!(in = fopen("digits.in", "r")) ||
      !(out = fopen("digits.out", "w"))) {
    fprintf(stderr, "Cannot open input/output files.\n");
    exit(1);
  }
    
  while (fscanf(in, "%d", &b) == 1 && b) {
    fscanf(in, "%d %d", &i, &n);
    if (b == 1) {
      /* it's easier if the rest of the code can assume b > 1 */
      fprintf(out, "%0*d\n", n, 1);
      continue;
    }

    bound = fast_exp(10, n);
    /*
    if ((ans = compute_plain(b, i, bound)) >= 0) {
      fprintf(out, "%d\n", ans);
    } else {
      ans = compute_mod(b, i, bound);
      fprintf(out, "%0*d\n", n, ans);
    }
    */
    fprintf(out, "%0*d\n", n, compute_mod(b, i, bound));
  }
  return 0;
}
  
