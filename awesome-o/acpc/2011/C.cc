//
// Idea: if f[N] is the answer for N, we look at the number of ways to
//       stack the bottom layer(s) and reduce to a smaller problem.  This
//       is slightly complicated by the fact that we can rotate in the
//       third dimension for more ways.

#include <iostream>

using namespace std;

typedef long long ll;

const int MAX_N = 1000000;

ll f[MAX_N+1];
ll partialf[MAX_N+1];     // f[0] + ... + f[N]
ll mod = 1000000007; 

int main()
{
  f[0] = 1;
  f[1] = 2;
  partialf[0] = 1;
  partialf[1] = 3;
  for (int N = 2; N <= MAX_N; N++) {
    f[N] = 0;

    // put two blocks horizontally on the bottom, there are two rotations
    // to do that
    f[N] += 2*f[N-1];
    f[N] %= mod;

    // put four blocks vertically, only one rotation
    f[N] += f[N-2];
    f[N] %= mod;

    // put one block horizontally, the other vertically in a zig-zag way,
    // then complete the zig-zag with a horizontal one.  There are four
    // rotations.
    //
    // f[N] += 4*(f[N-2] + f[N-3]+f[N-4]+...+f[0])
    f[N] += 4 * partialf[N-2];
    f[N] %= mod;

    partialf[N] = (f[N] + partialf[N-1]) % mod;
  }
  
  int T;
  cin >> T;
  while (T-- > 0) {
    int N;
    cin >> N;
    cout << f[N] << endl;
  }

  return 0;
}
