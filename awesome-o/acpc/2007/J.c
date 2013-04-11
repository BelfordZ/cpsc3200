/*
 * there are no tricks here...unless you want to be clever and realize
 * that you can just take n mod 9, and output the answer except to 
 * replace 0 by 9.
 *
 */

#include <stdio.h>
#include <assert.h>

int f(int x)
{
  int sum = 0;

  while (x > 0) {
    sum += x % 10;
    x /= 10;
  }

  return sum;
}

int ans(int n)
{
  while (n >= 10) {
    n = f(n);
  }
  return n;
}

int main(void)
{
  int n;
  
  while (scanf("%d", &n) == 1 && n) {
    printf("%d\n", ans(n));
    assert(ans(n) == (n % 9) ? n % 9 : 9);
  }
  return 0;
}
