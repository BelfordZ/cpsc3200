// howards BFS, modified

#include <iostream>
#include <cassert>
#include <algorithm>
#include <queue>

using namespace std;
const int MAX_NODES = 200;
struct Node {int deg, adj[MAX_NODES];};

// I use -1 to show unvisited, 0 as say red, 1 as black.
bool BFS_shortest_path(Node graph[], int D[]) {
   queue<int> q;
   int parent;
   
   for (int i = 0; i < MAX_NODES; i++) // set them all unvisited
      D[i] = -1;
   q.push(0);
   D[0] = 0; // color the first one '0'
   
   while (!q.empty()) {
      parent = q.front();
      q.pop();
      for (int k = 0; k < graph[parent].deg; k++) {
	 int child = graph[parent].adj[k];
	 if (D[child] == -1) { // if not visited
	    D[child] = 1 - D[parent]; // set child to what ever the parent isnt
	    q.push(child); // push the child onto the q
	 } else if (D[child] == D[parent]) // if same color as parent
	    return false;
      }
   }
   return true;
}

void clear(Node graph[], int n) {
   int i;
   for (i = 0; i < n; i++)
      graph[i].deg = 0;
}

void add_edge(Node graph[], int v, int w) {
   for (int i = 0; i < graph[v].deg; i++)
      if (graph[v].adj[i] == w) 
	 assert(0);
   graph[v].adj[graph[v].deg] = w;
   graph[v].deg++;
}

int main() {
   int numVertices = 0;
   int numEdges = 0;
   while (cin >> numVertices >> numEdges) {
      Node graph[MAX_NODES];
      int D[MAX_NODES];
      clear(graph, MAX_NODES);
      for (int i=0; i<numEdges; i++) {
	 int v1, v2;
	 cin >> v1 >> v2;
	 add_edge(graph, v1, v2);
      }
      if (BFS_shortest_path(graph, D))
	 cout << "BICOLORABLE." << endl;
      else
	 cout << "NOT BICOLORABLE." << endl;;
   }
   return 0;  
}
