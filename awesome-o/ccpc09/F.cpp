//
// Given N and K, the probability of seeing two queens of spades is
//
// K*(K-1)
// -------
// N*(N-1)
//
// setting this to be A/B gives:
//
// B*(K^2 - K) = A*(N^2 - N)
//
// So we try each possible N.  If A and B has no common factors, then
// B must divide into N^2 - N (so we can ignore those that don't).
// Then we can solve for K in
//
// K^2 - K - A*(N^2 - N)/B = 0
//
// by quadratic equation.  If K is an integer >= 0 then we have a solution.
//

#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

int gcd(int a, int b)
{
  int r;
  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}

void solve(int A, int B)
{
  int g = gcd(A, B);
  A /= g;
  B /= g;

  for (long long N = 2; N <= 1000000; N++) {
    long long c = N*(N-1);
    if (c % B != 0) {
      continue;
    }
    c /= B;

    long long disc = c*4*A + 1;
    long long root = (long long)floor(sqrt(disc));

    // if disc is a perfect square then it must be root^2 or (root+1)^2
    if (root*root != disc) {
      root++;
      if (root*root != disc) {
	continue;
      }
    }

    long long K1 = 1 - root;
    long long K2 = 1 + root;

    if (K1 >= 0 && K1 % 2 == 0) {
      cout << N << ' ' << K1/2 << endl;
      return;
    }
    if (K2 >= 0 && K2 % 2 == 0) {
      cout << N << ' ' << K2/2 << endl;
      return;
    }
  }

  // should never get here if there is a solution
  cout << "A = " << A << ", B = " << B << endl;
  assert(0);
}

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int A, B;

    cin >> A >> B;
    solve(A, B);
  }

  return 0;
}
