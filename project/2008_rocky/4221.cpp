/* Howard Cheng */

#include <fstream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cassert>

using namespace std;

const int MAX_M = 100000;
const int MAX_N = 100000;

ifstream in("park.in");
ofstream out("park.out");

struct Point {
  int x, y;
  bool visible;
};

/* sort by x first, then by y */
bool cmpx(const Point &p1, const Point &p2) 
{
  if (p1.x != p2.x) {
    return p1.x < p2.x;
  } else {
    return p1.y < p2.y;
  }
}

/* sort by y first, then by x */
bool cmpy(const Point &p1, const Point &p2) 
{
  if (p1.y != p2.y) {
    return p1.y < p2.y;
  } else {
    return p1.x < p2.x;
  }
}

/*
 * Binary Search
 *
 * Author: Howard Cheng
 *
 * Given a sorted array A of size n, it tries to find an item x in the
 * the array using binary search.  The function returns non-zero if
 * x is found, and zero otherwise.  Furthermore, if it is found, then
 * A[index] = x.  If it is not found, then index is the place x should
 * be inserted into A.
 *
 * ie.  A[i] <= x           for 0 <= i < index
 *              x < A[i]    for index <= i < n
 *
 * This routine is written for integer arrays, but can be adapted to
 * other types by changing the comparison operator.
 *
 * There is also an insert routine here that will insert the element into
 * the right place after the array has been reallocated (if necessary) to
 * store n+1 elements.
 *
 */

void bin_search(int *A, int n, int x, int &index)
{
   int l, u, m;

   if (n <= 0 || x < A[0]) {
      index = 0;
      return;
   }
   if (A[n-1] < x) {
      index = n;
      return;
   }
   l = 0;
   u = n-1;
   while (l+1 < u) {
      m = (l+u)/2;
      if (x >= A[m]) {
         l = m;
      } else {
         u = m;
      }
   }
   index = u;
}

istream &operator>>(istream &is, Point &p)
{
  p.visible = false;
  return is >> p.x >> p.y;
}

Point tree[MAX_N];
int vline[MAX_M], hline[MAX_M];

int main(void)
{
  int ntrees, npaths;
  int vnum, hnum;

  in >> ntrees >> npaths;
  for (int i = 0; i < ntrees; i++) {
    in >> tree[i];
  }

  vnum = hnum = 0;
  for (int i = 0; i < npaths; i++) {
    string path;
    in >> path;
    assert(path[1] == '=');
    if (path[0] == 'x') {
      path.erase(0,2);
      vline[vnum++] = atoi(path.c_str());
    } else {
      assert(path[0] == 'y');
      path.erase(0,2);
      hline[hnum++] = atoi(path.c_str());
    }
  }
  assert(hnum + vnum == npaths);

  sort(vline, vline+vnum);
  sort(hline, hline+hnum);

  int index;

  // see if each tree is visible by vertical paths
  sort(tree, tree+ntrees, cmpy);
  for (int i = 0; i < ntrees; i++) {
    // search to see where the closest vertical paths are
    bin_search(vline, vnum, tree[i].x, index);
    
    // see if it's visible from the path to the west
    if (index > 0 && 
	((i == 0) ||    // no one blocking
	 (tree[i-1].y != tree[i].y) ||
	 (tree[i-1].x < vline[index-1]))) {
      tree[i].visible = true;
      continue;
    }

    // see if it's visible from the path to the east
    if (index < vnum &&
	((i == ntrees-1) ||
	 (tree[i+1].y != tree[i].y) ||
	 (tree[i+1].x > vline[index]))) {
      tree[i].visible = true;
    }
  }

  // see if each tree is visible by horizontal paths
  sort(tree, tree+ntrees, cmpx);
  for (int i = 0; i < ntrees; i++) {
    if (tree[i].visible) continue;

    // search to see where the closest horizontal paths are
    bin_search(hline, hnum, tree[i].y, index);
    
    // see if it's visible from the path to the south
    if (index > 0 && 
	((i == 0) ||    // no one blocking
	 (tree[i-1].x != tree[i].x) ||
	 (tree[i-1].y < hline[index-1]))) {
      tree[i].visible = true;
      continue;
    }

    // see if it's visible from the path to the north
    if (index < hnum &&
	((i == ntrees-1) ||
	 (tree[i+1].x != tree[i].x) ||
	 (tree[i+1].y > hline[index]))) {
      tree[i].visible = true;
    }
  }
  
  int count = 0;
  for (int i = 0; i < ntrees; i++) {
    if (tree[i].visible) {
      count++;
    }
  }

  out << count << endl;

  return 0;
}
