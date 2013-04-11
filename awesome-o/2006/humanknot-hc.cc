/*
 * Solution for The Human Knot
 *
 * Howard Cheng
 *
 * The only unsolvable configuration occurs when the people form disjoint
 * cycles.  Otherwise, it is solvable.
 *
 * In the solvable case, the optimal solution must leave one person
 * unmoved.  So we try keeping each person stationary, and determine
 * the optimal solution with the person fixed.  So we find out what
 * the order of the other people should be.  Anyone else who is not
 * moved must form an increasing or decreasing subsequence (there are
 * two ways to sort the ring).  So we look for the longest increasing
 * and decreasing subsequence, and subtract the length from n-1.  This
 * gives us the minimum number of moves.
 *
 * Complexity: n stationary people, O(n log n) for increasing/decreasing
 * subsequence: O(n^2 log n).
 *
 * If we want to allow O(n^2) longest increasing subsequence as a solution,
 * just change maximum n to be 150 or so.
 *
 */

#include <fstream>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX_N = 500;

int graph[MAX_N+1][2];     /* use 1-based array */
int n;

/* longest increasing subsequence, return length */
int inc_seq(int *A, int n);
/* longest decreasing subsequence */
int dec_seq(int *A, int n);

/* figure out the correct order for each person, return number in the ring */
int fill_order(int start, int *order);

int read_case(void);
void solve_case(void);

ifstream in;
ofstream out;

int main(void)
{
  in.open("humanknot.in");
  out.open("humanknot.out");
  assert(in.good() && out.good());
  while (read_case()) {
    solve_case();
  }
  return 0;
}

/* longest increasing subsequence, return length */
int inc_seq(int *A, int n)
{
  int m[MAX_N+1], i, k, j, h, e;

  i = k = 1;
  m[1] = 0;
  for (; i < n; i++) {
    if (A[i] >= A[m[k]]) {
      m[k+1] = i;
      k++;
    } else if (A[i] < A[m[1]]) {
      m[1] = i;
    } else {
      assert(A[m[1]] <= A[i] && A[i] < A[m[k]]);
      h = 1;
      j = k;
      while (h != j-1) {
	e = (h+j)/2;
	if (A[m[e]] <= A[i]) {
	  h = e;
	} else {
	  j = e;
	}
      }
      m[j] = i;
    }
  }

  return k;
}

/* longest decreasing subsequence */
int dec_seq(int *A, int n)
{
  int B[MAX_N];
  int i;

  for (i = 0; i < n; i++) {
    B[i] = A[n-i-1];
  }
  return inc_seq(B, n);
}

int fill_order(int start, int *order)
{
  char used[MAX_N+1];
  int k = 0, t = start;

  /* order[k] is position of person start+k (mod n) */

  fill(used+1, used+n+1, 0);
  while (k < n) {
    order[(t+n-start)%n] = k++;
    used[t] = 1;
    if (!used[graph[t][0]]) {
      t = graph[t][0];
    } else if (!used[graph[t][1]]) {
      t = graph[t][1];
    } else {
      break;
    }
  }

  return k;
}

int read_case(void)
{
  int i;

  in >> n;
  if (!n) {
    return 0;
  }

  for (i = 1; i <= n; i++) {
    in >> graph[i][0] >> graph[i][1];
  }
  return 1;
}

void solve_case(void)
{
  int order[MAX_N];
  int fixed, t;
  int len = 0;

  for (fixed = 1; fixed <= n; fixed++) {
    if (fill_order(fixed, order) != n) {
      /* cannot get all n people, not solvable */
      out << "Not solvable." << endl;
      return;
    }
    if ((t = inc_seq(order+1, n-1)) > len) {
      len = t;
    }
    if ((t = dec_seq(order+1, n-1)) > len) {
      len = t;
    }
  }
  out << "Knot solvable." << endl;
  out << n-1-len << endl;
}

