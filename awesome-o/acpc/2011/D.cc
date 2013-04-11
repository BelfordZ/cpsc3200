// Knuth Art of Computer Programming vol 4A, 7.2.1.1, Exercise 69 (b).

#include <iostream>
#include <algorithm>

using namespace std;

void solve(int N)
{
  
  int num = (1 << N);
  int ones = num-1;

  int b = 0;
  while (b < num) {
    int a = (b >> 1) ^ b;
    if (b & 1) {
      a ^= ones;
    }

    if (b & (1 << (N-2))) {
      a ^= ((1 << (N-2)) | (1 << (N-1)));
    }

    cout << a << endl;

    b++;
  }
}

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int N;
    cin >> N;
    solve(N);
  }
  return 0;
}
