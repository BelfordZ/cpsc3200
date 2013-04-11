/* This is an O(n^2 log n) algorithm:
 *
 * - sort all points by x and y coordinates
 * - for each pair of points, we can assume that they are the diagonal of
 *   a square and find the other two points (with binary search)
 * - divide answer by 2 because there are two diagonals in a square
 *
 */

#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAX_N = 1000;

typedef pair<int, int> Point;

Point point[MAX_N];
int n;

int integer(double x)
{
  return fabs(floor(x+0.5)-x) <= 1e-10;
}

int good(int i, int j)
{
  double cx, cy;
  double vx, vy;
  double p1x, p1y, p2x, p2y;
  Point p1, p2;

  /* centre of square */
  cx = (point[i].first + point[j].first) / 2.0;
  cy = (point[i].second + point[j].second) / 2.0;

  /* a vector to one of the corners */
  vx = point[i].first - cx;
  vy = point[i].second - cy;

  /* figure out the other two corners */
  p1x = cx + vy;
  p1y = cy - vx;
  p2x = cx - vy;
  p2y = cy + vx;

  /* if they are too far away from an integer, quit */
  if (!(integer(p1x) && integer(p1y) && integer(p2x) && integer(p2y))) {
    return 0;
  }
  
  p1.first = static_cast<int>(floor(p1x + 0.5));
  p1.second = static_cast<int>(floor(p1y + 0.5));
  p2.first = static_cast<int>(floor(p2x + 0.5));
  p2.second = static_cast<int>(floor(p2y + 0.5));
  return binary_search(point, point+n, p1) && 
    binary_search(point, point+n, p2);
}

int count(void)
{
  int c = 0;

  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      if (good(i, j)) {
	c++;
      }
    }
  }
  return c/2;
}

int main(void)
{
  ifstream in("squares.in");
  ofstream out("squares.out");

  in >> n;
  while (n > 0) {
    for (int i = 0; i < n; i++) {
      in >> point[i].first >> point[i].second;
    }
    sort(point, point+n);
    out << count() << endl;
    in >> n;
  }
  return 0;
}
