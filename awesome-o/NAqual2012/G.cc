// There is really nothing to this problem.  Try to do everything with integer
// arithmetic.

#include <iostream>
#include <string>

using namespace std;

struct Rect
{
  int x1, y1, x2, y2;

  void read()
  {
    cin >> x1 >> y1 >> x2 >> y2;
  }

  bool inside(int x, int y) const
  {
    return (x1 <= x && x <= x2 && y1 <= y && y <= y2);
  }
};

struct Circle
{
  int x, y, r;

  void read()
  {
    cin >> x >> y >> r;
  }

  bool inside(int xx, int yy) const
  {
    int dist_sq = (x-xx)*(x-xx) + (y-yy)*(y-yy);
    return dist_sq <= r*r;
  }
};

int main()
{
  Rect rect[30];
  Circle circle[30];
  int n_rect = 0, n_circle = 0;

  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    string type;
    cin >> type;
    if (type == "rectangle") {
      rect[n_rect++].read();
    } else {
      circle[n_circle++].read();
    }
  }

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    int ans = 0;
    for (int k = 0; k < n_rect; k++) {
      if (rect[k].inside(x,y)) ans++;
    }
    for (int k = 0; k < n_circle; k++) {
      if (circle[k].inside(x,y)) ans++;
    }
    cout << ans << endl;
  }

  return 0;
}
