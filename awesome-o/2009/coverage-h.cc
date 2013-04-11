#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <iomanip>
#include <cassert>
#include <algorithm>

using namespace std;

const int MAX_TOWERS = 100;

struct Point {
public:
  int x, y;

  Point(int xx = 0, int yy = 0)
    : x(xx), y(yy) { };
};

istream &operator>>(istream &is, Point &p)
{
  return is >> p.x >> p.y;
}

bool do_case(void)
{
  int N;
  Point c0, c1, tower;
  int radius;
  vector< pair<double,double> > interval;

  cin >> N;
  if (!N) {
    return false;
  }

  cin >> c0 >> c1;
  for (int i = 0; i < N; i++) {
    cin >> tower >> radius;

    double A = c0.x - tower.x;
    double B = c1.x - c0.x;
    double C = c0.y - tower.y;
    double D = c1.y - c0.y;

    double a = B*B + D*D;
    double b = 2*(A*B + C*D);
    double c = A*A + C*C - radius*radius;

    double disc = b*b - 4*a*c;
    if (disc <= 0) continue;
    double r1 = (-b - sqrt(disc)) / (2*a);
    double r2 = (-b + sqrt(disc)) / (2*a);

    if (r1 < 0) r1 = 0;
    if (r2 < 0) r2 = 0;
    if (r1 > 1) r1 = 1;
    if (r2 > 1) r2 = 1;

    interval.push_back(make_pair(r1, r2));

  }
  sort(interval.begin(), interval.end());
 
  double covered = 0;
  double right = 0;
  
  for (unsigned int i = 0; i < interval.size(); i++) {
    if (interval[i].second <= right) continue;
    if (interval[i].first >= right) {
      covered += interval[i].second - interval[i].first;
      right = interval[i].second;
    } else {
      covered += interval[i].second - right;
      right = interval[i].second;
    }
  }
    
  assert(fabs(covered*100 - floor(covered*100) - 0.5) > 0.001);
  cout << fixed << setprecision(2) << covered*100 << endl;
  return true;
}

int main(void)
{
  while (do_case())
    ;
  return 0;
}
