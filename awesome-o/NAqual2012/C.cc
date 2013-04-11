// First, we have to remember to "flip" the top block upside down, so t(x)
// becomes -t(x).
//
// The height of the stacked block is simply the max of the sum of the two,
// so it is b(x) - t(x).
//
// The place with the largest gap is x such that b(x) - t(x) is minimized.
//
// The difference is the largest gap.
//
// To minimize/maximize a function: the minimum/maximum of a
// continuous (and differentiable) must be the places where f'(x) = 0,
// or at the end points of the interval.

#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Poly
{
  double b0, b1, b2, b3;

  void read()
  {
    cin >> b0 >> b1 >> b2 >> b3;
  }

  double eval(double x)
  {
    return b0 + b1*x + b2*x*x + b3*x*x*x;
  }

  double max()
  {
    double ans = std::max(eval(0), eval(1));
    double disc = b2*b2 - 3*b3*b1;
    if (disc >= 0) {
      double root1 = (-b2 + sqrt(disc)) / (3*b3);
      double root2 = (-b2 - sqrt(disc)) / (3*b3);

      if (0 <= root1 && root1 <= 1) {
	ans = std::max(ans, eval(root1));
      }
      if (0 <= root2 && root2 <= 1) {
	ans = std::max(ans, eval(root2));
      }
    }
    return ans;
  }

  double min()
  {
    double ans = std::min(eval(0), eval(1));
    double disc = b2*b2 - 3*b3*b1;
    if (disc >= 0) {
      double root1 = (-b2 + sqrt(disc)) / (3*b3);
      double root2 = (-b2 - sqrt(disc)) / (3*b3);

      if (0 <= root1 && root1 <= 1) {
	ans = std::min(ans, eval(root1));
      }
      if (0 <= root2 && root2 <= 1) {
	ans = std::min(ans, eval(root2));
      }
    }
    return ans;
  }

  Poly add(Poly p)
  {
    Poly ans;
    ans.b0 = b0 + p.b0;
    ans.b1 = b1 + p.b1;
    ans.b2 = b2 + p.b2;
    ans.b3 = b3 + p.b3;
    return ans;
  }

  void neg()
  {
    b0 = -b0;
    b1 = -b1;
    b2 = -b2;
    b3 = -b3;
  }
};
  
int main()
{
  while (true) {
    Poly b, t;
    b.read();
    t.read();
    if (cin.eof()) break;

    // flip top block upside down
    t.neg();

    Poly sum = b.add(t);

    cout << fixed << setprecision(6) << sum.max() - sum.min() << endl;
  }
   
  
  return 0;
}
