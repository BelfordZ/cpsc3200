//
// The idea is that each term is the sum of the previous N terms mod 10.
// This is just a linear recurrence (Fibonacci mod 10 if N = 2) but the
// number of terms can be very large.  We cannot compute every term one
// by one.
//
// We note that if we write n consecutive values into a vector 
//
// b(i) = [ f(i) f(i-1) ... f(i-n+1) ]
//
// then
//
// b(i+n) = A^n . b(i) mod 10
//
// where A is the matrix
//
// [ 1 1 ... 1 ]
// [ 1 0 ... 0 ]
// [ 0 1 ... 0 ]
// [  ...      ]
// [ 0 0 ... 1 ]
//
// so b(k) = A^(k-(N-1)) b(N-1) mod 10         for k >= N-1
//
// where b(N-1) contain the initial part of the sequence.
//
// The matrix exponentiation can be computed by fast exponentiation.
//

#include <iostream>

using namespace std;

// Matrix multiplication: A = A * B
void mult(int A[8][8], int B[8][8], int N)
{
  int C[8][8];

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      C[i][j] = 0;
      for (int k = 0; k < N; k++) {
	C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % 10;
      }
    }
  }
  
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      A[i][j] = C[i][j];
    }
  }
}

void solve(int A[8][8], int b[8], int N, long long K)
{
  // one of the base cases
  if (K <= N-1) {
    cout << b[N-1-K] << endl;
    return;
  }

  // fast exponentiation for A^(K-(N-1))
  int res[8][8], x[8][8];
  
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      res[i][j] = (i == j);
      x[i][j] = A[i][j];
    }
  }


  K -= (N-1);
  while (K > 0) {
    if (K & 0x01) {
      K--;
      mult(res, x, N);
    } else {
      K >>= 1;
      mult(x, x, N);
    }
  }
  
  // compute the first component of A^(K-(N-1)) * b(N-1)
  int ans = 0;
  for (int i = 0; i < N; i++) {
    ans = (ans + res[0][i] * b[i]) % 10;
  }

  cout << ans << endl;

}

void do_case(void)
{
  int N;
  int A[8][8];
  int b[8];

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> b[N-1-i];
    for (int j = 0; j < N; j++) {
      if (i == 0) {
	A[i][j] = 1;
      } else {
	A[i][j] = (i-1 == j);
      }
    }
  }

  long long M, K;
  cin >> M;
  while (M-- > 0) {
    cin >> K;
    solve(A, b, N, K);
  }
}

int main(void)
{
  int C;
  cin >> C;
  while (C-- > 0) {
    do_case();
  }

  return 0;
}
