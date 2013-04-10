#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;
const int MAX_NODES = 10;
const int DISCONNECT = -1;

/* assume that D and P have been allocated */
void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int src, int D[]) {
   char used[MAX_NODES];
   int fringe[MAX_NODES];
   int f_size;
   int v, w, j, wj;
   int best, best_init;
   
   f_size = 0;
   for (v = 0; v < n; v++) {
      if (graph[src][v] != DISCONNECT && src != v) {
	 D[v] = graph[src][v];
	 fringe[f_size++] = v;
	 used[v] = 1;
      } else {
	 D[v] = DISCONNECT;
	 used[v] = 0;
      }
   }
   D[src] = 0;
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

int main(void)
{
   int m, w, num;
   int i, j;
   int graph[MAX_NODES][MAX_NODES];
   int D[MAX_NODES][MAX_NODES];
   int path[MAX_NODES];
   
   /* clear graph */
   for (i = 0; i < MAX_NODES; i++) {
      for (j = 0; j < MAX_NODES; j++) {
	 graph[i][j] = DISCONNECT;
      }
   }
   
   /* read graph */
   cin >> i >> j >> w;
   while (!(i == -1 && j == -1)) {
      assert(0 <= i && i < MAX_NODES && 0 <= j && j < MAX_NODES);
      graph[i][j] = graph[j][i] = w;
      cin >> i >> j >> w;
   }
   
   for (i = 0; i < MAX_NODES; i++) {
      dijkstra(graph, MAX_NODES, i, D[i], P[i]);
   }
   
   /* do queries */
   cin >> i >> j;
   while (!(i == -1 && j == -1)) {
      assert(0 <= i && i < MAX_NODES && 0 <= j && j < MAX_NODES);
      cout << i << " " << j << ": " << D[i][j] << endl;
     
      num = get_path(j, P[i], path);
      for (m = 0; m < num; m++) {
	 cout << " " << path[m];
      }
      cin >> i >> j;
   }
   
   return 0;
}

int main() {
   int numCities, numRoads;
   cin >> numCities >> numRoads;

   //make and init map to all disconnected.
   pair<int, int> g[1000][1000], d[1000][1000];
   
   for (i = 0; i < 1000; i++) {
      for (j = 0; j < 1000; j++) {
	 g[i][j].first = -1;
      }
   }
   int gasPrices[1000];
   for (int i = 0; i < numCities; i++) {
      cin >> gasPrices[i];
      
   }
   for (int i = 0; i < numRoads; i++) {
      int u, v, d;
      cin >> u >> v >> d;
   }
   
   // test cases
   int numQ;
   cin >> numQ;
   for (int i = 0; i < numQ; i++) {
      int c, s, e;
      cin >> c >> s >> e;
   }
}
