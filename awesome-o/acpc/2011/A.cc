// The only choices we have is when a bit is 1 in A|B but 0 in A&B.  To
// make sure B >= A we want the leftmost such bit to be 1 in B and 0 in
// A.  To minimize difference, we want all other such bits to be 0 in B
// and 1 in A.

#include <iostream>

using namespace std;

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int C, D;
    cin >> C >> D;
    
    int A, B;
    A = B = 0;
    
    bool first = true;
    bool good = true;
    for (int i = 30; i >= 0; i--) {
      int mask = 1 << i;
      good &= !((C & mask) && !(D & mask));
      if (C & mask) {
	A |= mask;
	B |= mask;
      } else if (D & mask) {
	if (first) {
	  B |= mask;
	  first = false;
	} else {
	  A |= mask;
	}
      }
    }
    if (!good) {
      cout << -1 << endl;
    } else {
      cout << A << ' ' << B << endl;
    }
  }
  
  return 0;
}
