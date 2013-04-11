#include <iostream>
#include <cassert>

using namespace std;

const int MAX_DECKS = 10;
const int MAX_CARDS = MAX_DECKS * 52;

long long gcd(long long a, long long b, long long &s, long long &t)
{
  long long r, r1, r2, a1, a2, b1, b2, q;

  /* unnecessary if a, b >= 0 */
  if (a < 0) {
    r = gcd(-a, b, s, t);
    s *= -1;
    return r;
  }
  if (b < 0) {
    r = gcd(a, -b, s, t);
    t *= -1;
    return r;
  }

  a1 = b2 = 1;
  a2 = b1 = 0;

  while (b) {
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

  s = a1;
  t = a2;
  return a;
}

long long chrem(int N, long long rem[], long long mod[])
{
  long long rem_so_far = rem[0];
  long long mod_so_far = mod[0];

  for (int i = 1; i < N; i++) {
    // since x = s * mod_so_far + rem_so_far
    //         = t * mod[i] + rem[i]
    // 
    // we solve diophantine equation:
    //
    // mod_so_far * s - mod[i] * t = rem[i] - rem_so_far
    //
    long long a = mod_so_far, b = -mod[i], c = rem[i] - rem_so_far;
    long long s0, t0;
    long long g = gcd(a, b, s0, t0);

    if (c % g != 0) {
      // no solution
      return -1;
    }

    s0 *= c/g;
    t0 *= c/g;

    // general solution to the equation is:
    //
    // a * (s0 + k*(b/g)) + b * (t0 - k*(a/g)) = c
    //
    // so we have:
    //
    // x =   a  * (s0 + k*(b/g)) + rem_so_far
    // x = (-b) * (t0 - k*(a/g)) + rem[i]
    //
    // Note: b = -mod[i]
    //
    // so we have:
    //
    // x = (a/g)*b * k + rem_so_far + mod_so_far * s0
    //   = (b/g)*a * k + rem[i] + mod[i] * t0
    long long limit = (long long)((1ULL << 63) - 1);
    // the test below is perhaps a little bit conservative but should be okay
    if ((s0 > 0 && limit / s0 < mod_so_far) ||
	(s0 < 0 && limit / s0 > mod_so_far) ||
	limit - rem_so_far < mod_so_far * s0 ||
	mod[i] > limit / (mod_so_far / g)) {
      cout << "mod_so_far = " << mod_so_far << endl;
      cout << "s0 = " << s0 << endl;
      cout << "rem_so_far = " << rem_so_far << endl;
      cout << "Bad input: modulus too big" << endl;
      return -1;
    }

    rem_so_far += mod_so_far * s0;
    mod_so_far = (mod_so_far/g) * mod[i];
    rem_so_far %= mod_so_far;
    if (rem_so_far < 0) {
      rem_so_far += mod_so_far;
    }

    assert(rem_so_far < (long long)((1ULL << 31) - 1));
  }

  return rem_so_far;
}

long long solve(int N, const int once[], const int want[])
{
  // compute permutation so perm[k] => position k in shuffling
  int perm[MAX_CARDS];
  for (int i = 0; i < N; i++) {
    perm[once[i]] = i;
  }

  // now trace each element
  long long cycle_len[MAX_CARDS], rem[MAX_CARDS];

  for (int i = 0; i < N; i++) {
    int count = 1;
    int where = perm[i];
    rem[i] = (want[where] == i) ? 1 : -1;
    
    // must repeat after N+1 steps
    while (where != i && count <= N+1) {
      where = perm[where];
      count++;
      if (want[where] == i) {
	rem[i] = count;
      }
    }
    cycle_len[i] = count;

    // impossible
    if (rem[i] == -1) {
      return -1;
    }

    rem[i] %= cycle_len[i];
  }

  // apply Chinese remaindering
  return chrem(N, rem, cycle_len);
}

int main(void)
{
  int N;
  int once[MAX_CARDS], want[MAX_CARDS];

  while (cin >> N && N > 0) {
    for (int i = 0; i < N; i++) {
      cin >> once[i];
      once[i]--;
    }
    for (int i = 0; i < N; i++) {
      cin >> want[i];
      want[i]--;
    }

    cout << solve(N, once, want) << endl;
  }

  return 0;
}
