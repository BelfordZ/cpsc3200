/*
 * Solution for Random Walk
 *
 * Howard Cheng
 *
 * The idea is as follows.  For each v_i, we find the line l_i
 * perpendicular to v_i.  Each l_i separates the plane into two
 * halves: H_i (the half containing v_i) and h_i (the other half).
 *
 * Look at v = alpha_1 * v_1 + ... + alpha_n * v_n, where alpha_i = +/-1
 *
 * If alpha_i = 1 but v is in h_i, then by changing alpha_i to -1 we
 * will definitely get a longer vector (we are moving perpendicularly away
 * from l_i which goes through the origin).  On the other hand if
 * alpha_i = -1 but v is in H_i then we can change alpha_i to 1 to get
 * a longer vector.
 *
 * This means that any optimal vector v must have alpha_i = +1 if it's in 
 * H_i and -1 if it's in h_i.
 *
 * So if we look at all l_i's, this partition the plane into a number
 * of regions.  Each region contains a potential optimal solution, and
 * the region specifies the alpha_i's.  It's also easy to go from one
 * region to the next one (if l_i separates the two regions, we just
 * need to change alpha_i).
 *
 * There are n lines, so there are O(n) regions.  We can sort the
 * lines by angle to get the regions into order.  Complexity is 
 * O(n log n).  n <= 100 makes exhaustive search infeasible.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define MAX_N 100

typedef struct {
  int x, y;
} Vector;

/* 
 * for each v_i, we store two vectors (point to opposite directions)
 * defining l_i.  When we cross one of the two vectors during the
 * sweep (counterclockwise), we have to change alpha_i from -1 to +1
 * or vice versa.
 *
 */

typedef struct {
  Vector dir;       
  int index;        /* which vector it is associated to */
  int change;       /* +2 if v_i is to the left of dir, -2 otherwise */
} Line;

Vector v[MAX_N];
int n;
int case_no = 0;

int read_case(void);
void solve_case(void);
int cmp(const void *a, const void *b);
double length(Vector v);

int main(void)
{
  freopen("randomwalk.in", "r", stdin);
  freopen("randomwalk.out", "w", stdout);

  while (read_case()) {
    solve_case();
  }
  return 0;
}

int read_case(void)
{
  int i;

  scanf("%d", &n);
  if (!n) {
    return 0;
  }
  for (i = 0; i < n; i++) {
    scanf("%d %d", &(v[i].x), &(v[i].y));
  }
  return 1;
}

void solve_case(void)
{
  Vector sum;
  double dist = 0.0, temp;
  int i;

  /* for each vector, we store two vectors (in each direction) */
  Line line[2*MAX_N];

  for (i = 0; i < n; i++) {
    line[2*i].dir.x = v[i].y;
    line[2*i].dir.y = -v[i].x;   /* v[i] is to the left */
    line[2*i].index = i;
    line[2*i].change = 2;

    line[2*i+1].dir.x = -v[i].y;
    line[2*i+1].dir.y = v[i].x;  /* v[i] is to the right */
    line[2*i+1].index = i;
    line[2*i+1].change = -2;
  }

  /* sort into regions */
  qsort(line, 2*n, sizeof(Line), cmp);

  /* figure out vector in first region */
  /* any group of n consecutive lines must have different indices */
  sum.x = sum.y = 0;
  for (i = 0; i < n; i++) {
    if (line[i].change > 0) {
      /* change to positive, so we must be negative */
      sum.x -= v[line[i].index].x;
      sum.y -= v[line[i].index].y;
    } else {
      /* positive */
      sum.x += v[line[i].index].x;
      sum.y += v[line[i].index].y;
    }
  }
  dist = length(sum);

  /* now sweep across: we only need to sweep half the plane, but let's
     just be safe */
  for (i = 0; i < 2*n-1; i++) {
    sum.x += line[i].change * v[line[i].index].x;
    sum.y += line[i].change * v[line[i].index].y;
    if ((temp = length(sum)) > dist) {
      dist = temp;
    }
  }

  printf("Maximum distance = %.3f meters.\n", dist);
}

/* sort by angle */
int cmp(const void *a, const void *b)
{
  const Line *x = (const Line *)a, *y = (const Line *)b;
  double t1, t2;
  t1 = atan2(x->dir.y, x->dir.x);
  t2 = atan2(y->dir.y, y->dir.x);

  assert(fabs(t1-t2) >= 1e-4);   /* no parallel vectors */
  if (t1 < t2) {
    return -1;
  } else if (t1 > t2) {
    return 1;
  }
}

double length(Vector v)
{
  return sqrt((double)v.x*v.x + (double)v.y*v.y);
}
