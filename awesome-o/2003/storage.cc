#define PROBLEM 0 /* The problem # here */ 
#define TEAM 0 /* Your team # here */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

ifstream in;
ofstream out; 
void solve_problem();

int main(void)
{
  char filename[64];
  sprintf(filename, "prob%d.dat", PROBLEM); 

  in.open(filename, ios::in); 
  sprintf(filename, "prob%d.out", PROBLEM); 
  out.open(filename, ios::out); 
  out << "Program " << PROBLEM << " by team " << TEAM << endl;
  solve_problem(); 
  out << "End of program " << PROBLEM << " by team " << TEAM << endl;
  return 0; 
}

const int MAX_N = 5000;
const int MAX_M = 5000;

/* how close to call equal */
#define EPSILON 1E-8

struct Point {
  double x, y;
};

struct Line {
  Point U, L;
  bool operator<(const Line &l) const {
    return U.x < l.U.x;
  }
};  

/* counterclockwise, clockwise, or undefined */
enum {CCW, CW, CNEITHER};

int ccw(Point a, Point b, Point c)
{
  double dx1 = b.x - a.x;
  double dx2 = c.x - b.x;
  double dy1 = b.y - a.y;
  double dy2 = c.y - b.y;
  double t1 = dy2 * dx1;
  double t2 = dy1 * dx2;

  assert(fabs(t1 - t2) > EPSILON);
  if (t1 > t2) {
    return CCW;
  } else {
    return CW;
  }
}

int binsearch(Line *cardboard, int n, Point toy)
{
  int hi, lo, mid, orient;

  if (ccw(cardboard[0].L, cardboard[0].U, toy) == CCW) {
    /* to the left of the first cardboard */
    return 0;
  }
  if (ccw(cardboard[n-1].L, cardboard[n-1].U, toy) == CW) {
    /* to the right of the last cardboard */
    return n;
  }

  lo = 0;
  hi = n-1;

  while (hi - lo > 1) {
    mid = (lo + hi) / 2;
    orient = ccw(cardboard[mid].L, cardboard[mid].U, toy);
    if (orient == CCW) {
      /* to the left */
      hi = mid;
    } else if (orient == CW) {
      /* to the right */
      lo = mid;
    } else {
      assert(0);
    }
  }

  return lo+1;
}

void solve_problem(void)
{
  int n, m;
  double x1, y1, x2, y2;
  int partition[MAX_N+1];
  Line cardboard[MAX_N];
  Point toy;
  int first = 1;
  int i;
  
  while (in >> n && n > 0) {
    if (first) {
      first = 0;
    } else {
      out << endl;
    }

    for (i = 0; i <= n; i++) {
      partition[i] = 0;
    }

    in >> m >> x1 >> y1 >> x2 >> y2;
    for (i = 0; i < n; i++) {
      in >> cardboard[i].U.x >> cardboard[i].L.x;
      cardboard[i].U.y = y1;
      cardboard[i].L.y = y2;
    }

    //    sort(cardboard, cardboard+n);

    for (i = 0; i < m; i++) {
      in >> toy.x >> toy.y;
      assert(x1 <= toy.x && toy.x <= x2 && y2 <= toy.y && toy.y <= y1);
      partition[binsearch(cardboard, n, toy)]++;
    }

    for (i = 0; i <= n; i++) {
      out << i << ": " << partition[i] << endl;
    }
  }
}
