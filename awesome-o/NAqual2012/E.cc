// Just look for the largest number that is relatively prime to
// everything else.  Make sure you quit as soon as possible.  It
// should be clear that the only numbers you get to keep are the ones
// that have no common factors with anything else.

#include <iostream>
#include <algorithm>

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

int main(void)
{
  int n;
  int A[1000];
  while (cin >> n) {
    for (int i = 0; i < n; i++) {
      cin >> A[i];
    }
    sort(A, A+n);

    bool bad[1000] = {false};
    for (int i = n-1; i >= 0; i--) {
      for (int j = i-1; j >= 0; j--) {
	if (gcd(A[i], A[j]) > 1) {
	  bad[i] = bad[j] = true;
	}
      }
      if (!bad[i]) {
	cout << A[i] << endl;
	break;
      }
    }
  }
  return 0;
}
