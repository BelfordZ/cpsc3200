#include <iostream>
#include <climits>
#include <cassert>
#include <algorithm>
#include <string>

using namespace std;

const int MAX_TASKS = 100;
const int MAX_NODES = MAX_TASKS+1;
const int DISCONNECT = INT_MAX;

bool bellmanford(int graph[MAX_NODES][MAX_NODES], int n, int src,
		 int D[])
{
  int v, w, k;

  for (v = 0; v < n; v++) {
    D[v] = INT_MAX;
  }
  D[src] = 0;

  for (k = 0; k < n-1; k++) {
    for (v = 0; v < n; v++) {
      for (w = 0; w < n; w++) {
	if (graph[v][w] != DISCONNECT && D[v] != INT_MAX) {
	  if (D[w] == INT_MAX || D[w] > D[v] + graph[v][w]) {
	    D[w] = D[v] + graph[v][w];
	  }
	}
      }
    }
  }

  for (v = 0; v < n; v++) {
    for (w = 0; w < n; w++) {
      if (graph[v][w] != DISCONNECT && D[v] != INT_MAX) {
        if (D[w] == INT_MAX || D[w] > D[v] + graph[v][w]) {
	  return false;
	}
      }
    }
  }
  return true;
}

bool do_case(void)
{
  int n;
  cin >> n;
  if (n == 0) {
    return false;
  }
  
  // clear graph
  int graph[MAX_NODES][MAX_NODES];
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      graph[i][j] = DISCONNECT;
    }
  }

  for (int i = 1; i <= n; i++) {
    graph[0][i] = 0;
  }
    
  // read constraints
  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    int task1, task2, A;
    string garbage;
    string key;
    cin >> garbage >> task1 >> garbage;
    cin >> key;
    if (key == "at") {
      cin >> garbage >> A >> garbage >> garbage >> garbage >> garbage >> task2;
      graph[task1][task2] = min(graph[task1][task2], -A);
    } else {
      assert(key == "within");
      cin >> A >> garbage >> garbage >> garbage >> garbage >> garbage
	  >> garbage >> garbage >> task2;
      graph[task2][task1] = min(graph[task2][task1], A);
      graph[task1][task2] = min(graph[task1][task2], 0);
    }
  }

  int D[MAX_NODES];
  if (bellmanford(graph, n+1, 0, D)) {
    int adj = *min_element(D+1, D+n+1);
    for (int i = 1; i <= n; i++) {
      cout << D[i] - adj + 1 + INT_MAX;
      if (i < n) {
	cout << ' ';
      } else {
	cout << endl;
      }
    }
  } else {
    cout << "Impossible." << endl;

  }

  return true;
}

int main(void)
{
  while (do_case())
    ;
  return 0;
}
