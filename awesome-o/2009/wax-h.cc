#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <cassert>

using namespace std;

struct Point {
  double x, y;

  Point(double xx = 0, double yy = 0) 
    : x(xx), y(yy) { };
};

double dist(const Point &p1, const Point &p2)
{
  return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

double area(const Point &p1, const Point &p2, const Point &p3)
{
  double a = dist(p1,p2), b = dist(p2,p3), c = dist(p1,p3);
  double s = (a+b+c)/2;
  return sqrt(s * (s-a) * (s-b) * (s-c));
}

Point midpoint(const Point &p1, const Point &p2)
{
  return Point((p1.x+p2.x)/2, (p1.y+p2.y)/2);
}

ostream &operator<<(ostream &os, const Point &p)
{
  os << p.x << ' ' << p.y;
  //  assert(fabs(p.x*1000-floor(p.x*1000)-0.5) > 0.001 &&
  //	 fabs(p.y*1000-floor(p.y*1000)-0.5) > 0.001);
  return os;
}

void solve(int W, int H, int D, int workers)
{
  double A = W * H;

  Point last(W,0), door(D, 0);
  Point lo, hi, mid;

  for (int i = 0; i < workers-1; i++) {
    double piece = A / workers;

    if (last.x == W) {
      // last is on the east wall
      if (area(last, door, Point(W,H)) >= piece) {
	lo = last;
	hi = Point(W,H);
	goto binsearch;
      } else {
	piece -= area(last, door, Point(W,H));
	last = Point(W,H);
      }
    }
    if (last.y == H) {
      // last is on the north wall
      if (area(last, door, Point(0,H)) >= piece) {
	lo = last;
	hi = Point(0,H);
	goto binsearch;
      } else {
	piece -= area(last, door, Point(0,H));
	last = Point(0,H);
      }
    }
    assert(last.x == 0);

    // last is on the east wall
    lo = last;
    hi = Point(0,0);

  binsearch:
    mid = midpoint(lo, hi);
    double testarea = area(last, door, mid);
    while (dist(lo, hi) >= 1e-8) {
      if (testarea > piece) {
	hi = mid;
      } else {
	lo = mid;
      }
      mid = midpoint(lo, hi);
      testarea = area(last, door, mid);
    }

    if (i) cout << ' ';
    cout << fixed << setprecision(3) << mid;
    last = mid;
  }
  cout << endl;
}

int main(void)
{
  int W, H, D, workers;
  while (cin >> W >> H >> D >> workers &&
	 (W || H || D || workers)) {
    solve(W, H, D, workers);
  }

  return 0;
}
