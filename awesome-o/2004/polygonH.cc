#include <fstream>
#include <algorithm>

using namespace std;

struct Point {
  int x, y;
};

/* counterclockwise, clockwise, or undefined */
enum {CCW, CW, CNEITHER};

Point start_p;

int ccw(Point a, Point b, Point c)
{
  int dx1 = b.x - a.x;
  int dx2 = c.x - b.x;
  int dy1 = b.y - a.y;
  int dy2 = c.y - b.y;
  int t1 = dy2 * dx1;
  int t2 = dy1 * dx2;

  if (t1 == t2) {
    if (dx1 * dx2 < 0 || dy1 * dy2 < 0) {
      if (dx1*dx1 + dy1*dy1 >= dx2*dx2 + dy2*dy2) {
        return CNEITHER;
      } else {
        return CW;
      }
    } else {
      return CCW;
    }
  } else if (t1 > t2) {
    return CCW;
  } else {
    return CW;
  }
}

bool operator<(const Point &p1, const Point &p2)
{
  return ccw(start_p, p1, p2) == CCW;
}

istream &operator>>(istream &is, Point &p)
{
  return is >> p.x >> p.y;
}

ostream &operator<<(ostream &os, Point p)
{
  return os << "(" << p.x << "," << p.y << ")";
}

const int MAX_POINT = 1000;

int main(void)
{
  Point polygon[MAX_POINT+1];
  int n, i;
  ifstream in("polygon.in");
  ofstream out("polygon.out");

  n = 0;
  while (in >> polygon[n]) {
    n++;
  }
  start_p = polygon[0];
  sort(polygon, polygon+n);
  for (i = 0; i < n; i++) {
    out << polygon[i] << endl;
  }
  return 0;
}
