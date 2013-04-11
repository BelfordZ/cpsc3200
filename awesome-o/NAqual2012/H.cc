// This is just shortest path problem.  The nodes are the shady spots (plus
// the start and destination), and the edge costs are the squared distances.
// This is a dense graph so we may as well use the O(n^2) version.

/*
 * Dijkstra's Algorithm
 *
 * Author: Howard Cheng
 * Reference:
 *   Ian Parberry's "Problems on Algorithms", page 102.
 *
 * Given a weight matrix representing a graph and a source vertex, this
 * algorithm computes the shortest distance, as well as path, to each
 * of the other vertices.  The paths are represented by an inverted list,
 * such that if v preceeds immediately before w in a path from the
 * source to vertex w, then the path P[w] is v.  The distances from
 * the source to v is given in D[v] (DISCONNECT if not connected).
 *
 * Call get_path to recover the path.
 *
 * Note: Dijkstra's algorithm only works if all weight edges are
 *       non-negative.
 *
 */

#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX_NODES = 2510;
const int DISCONNECT = -1;

/* assume that D and P have been allocated */
void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int src, int D[], 
	      int P[])
{
  char used[MAX_NODES];
  int fringe[MAX_NODES];
  int f_size;
  int v, w, j, wj;
  int best, best_init;

  f_size = 0;
  for (v = 0; v < n; v++) {
    if (graph[src][v] != DISCONNECT && src != v) {
      D[v] = graph[src][v];
      P[v] = src;
      fringe[f_size++] = v;
      used[v] = 1;
    } else {
      D[v] = DISCONNECT;
      P[v] = -1;
      used[v] = 0;
    }
  }
  D[src] = 0;
  P[src] = -1;
  used[src] = 1;

  best_init = 1;
  while (best_init) {
    /* find unused vertex with smallest D */
    best_init = 0;
    for (j = 0; j < f_size; j++) {
      v = fringe[j];
      assert(D[v] != DISCONNECT);
      if (!best_init || D[v] < best) {
        best = D[v];
        w = v;
        wj = j;
        best_init = 1;
      }
    }

    if (best_init) {
      assert(D[w] != DISCONNECT);
      assert(fringe[wj] == w);

      /* get rid of w from fringe */
      f_size--;
      for (j = wj; j < f_size; j++) {
        fringe[j] = fringe[j+1];
      }

      /* update distances and add new vertices to fringe */
      for (v = 0; v < n; v++) {
        if (v != src && graph[w][v] != DISCONNECT) {
          if (D[v] == DISCONNECT || D[w] + graph[w][v] < D[v]) {
            D[v] = D[w] + graph[w][v];
            P[v] = w;
          } else if (D[w] + graph[w][v] == D[v]) {
            /* put tie-breaker here */
          }
          if (!used[v]) {
            used[v] = 1;
            fringe[f_size++] = v;
          }
        }
      }
    }
  }
  D[src] = 0;
}

int get_path(int v, int P[], int path[])
{
  int A[MAX_NODES];
  int i, k;

  k = 0;
  A[k++] = v;
  while (P[v] != -1) {
    v = P[v];
    A[k++] = v;
  }
  for (i = k-1; i >= 0; i--) {
    path[k-1-i] = A[i];
  }
  return k;
}

int graph[MAX_NODES][MAX_NODES];
int P[MAX_NODES], D[MAX_NODES];
int path[MAX_NODES];

typedef pair<int,int> pii;
int main(void)
{
  int n;
  cin >> n;

  pii p[2502];
  for (int i = 1; i <= n; i++) {
    cin >> p[i].first >> p[i].second;
  }
  cin >> p[0].first >> p[0].second;
  cin >> p[n+1].first >> p[n+1].second;
  
  for (int i = 0; i < n+2; i++) {
    graph[i][i] = 0;
    for (int j = i+1; j < n+2; j++) {
      int d1 = p[i].first - p[j].first;
      int d2 = p[i].second - p[j].second;
      graph[i][j] = graph[j][i] = d1*d1 + d2*d2;
    }
  }

  dijkstra(graph, n+2, 0, D, P);
  int num = get_path(n+1, P, path);
  if (num == 2) {
    cout << "-" << endl;
  } else {
    for (int m = 1; m < num-1; m++) {
      cout << path[m]-1 << endl;
    }
  }

  return 0;
}
