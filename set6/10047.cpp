// I give up. Spent to much time restarting. My approach was to create a
// weighted graph. an edge is made between any 4-connected nbr who
// isnt blocked (!= #). THe cost is determined by how many times you need to
// changed direction plus the step. there is a lot of little sub problems that
// I wasn't able to do :(. 

/*
 * Shortest Path with BFS
 *
 * Author: Howard Cheng
 *
 * Given a graph represented by an adjacency list, this algorithm uses
 * BFS to find the shortest path from a source vertex to each of the
 * other vertices.  The distances from the source to v is given in D[v], and
 * D[v] is set to -1 if the source vertex is not connected to w.  Also,
 * the shortest path tree is stored in the array P.
 *
 * Call get_path to recover the path.
 * 
 * Note: All edges must have the same cost for this to work.
 *       This algorithm has complexity O(n+m).
 *
 */

#include <iostream>
#include <cassert>
#include <algorithm>
#include <queue>

using namespace std;

const int MAX_NODES = 100;

struct Node {
  int deg;           /* number of outgoing edges */
  int adj[MAX_NODES];
  
  /* the following is not necessary, but useful in many situations */
  int cost[MAX_NODES];
};

void BFS_shortest_path(Node graph[], int n, int src, int D[], int P[])
{
  char used[MAX_NODES];
  queue<int> q;
  int i, v, w;

  fill(used, used+MAX_NODES, 0);
  q.push(src);
  used[src] = 1;

  for (i = 0; i < MAX_NODES; i++) {
    D[i] = -1;
    P[i] = -1;
  }
  D[src] = 0;

  while (!q.empty()) {
    v = q.front();
    q.pop();
    for (i = 0; i < graph[v].deg; i++) {
      w = graph[v].adj[i];
      if (!used[w]) {
	D[w] = D[v] + 1;
	P[w] = v;
	q.push(w);
	used[w] = 1;
      } else if (D[v] + 1 == D[w]) {
	/* put tie-breaker here */
	/* eg. find largest path in lexicographic order, when the path */
        /*     is considered in REVERSE!                               */
	P[w] = max(P[w], v);
      }
    }
  }
}

void clear(Node graph[], int n)
{
  int i;
  for (i = 0; i < n; i++) {
    graph[i].deg = 0;
  }
}

void add_edge(Node graph[], int v, int w, int cost)
{
  int i;

  /* make sure that we have no duplicate edges */
  for (i = 0; i < graph[v].deg; i++) {
    if (graph[v].adj[i] == w) {
      assert(0);
    }
  }

  graph[v].cost[graph[v].deg] = cost;
  graph[v].adj[graph[v].deg] = w;
  graph[v].deg++;
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

char facing = 'N';

//cost of turning
int SND = 2;
int EWD = 2;
int WND = 1;
int WSD = 1;
int ESD = 1;
int END = 1;
int main(void)
{
   int rowMax, colMax;
   // get dat inputs
   while ((cin >> rowMax >> colMax)) {

      (rowMax != 0 && colMax != 0) ?
	 break :
	 vector<vector<int> > squares[rowMax][colMax];
      
      Node *graph = new Node[colMax*rowMax];

      for(int row = 0; row < rowMax; row++) {
	 for(int col = 0; col < colMax; col++) {
	    char square;
	    cin >> square;

	    squares[row][col] = square;
	 }
      }
      for(int row = 0; row < rowMax; row++) {
	 for(int col = 0; col < colMax; col++) {
	    if (square[row][col] != '#') { // we dont want to connect these
	       if ((row-1 >= 0) && (row+1 < rowMax)) { // stay inbounds
		  if (square[row-1][col] != '#') {
		     int moveCost = 0;
		     switch(facing){
			case 'n':
			   moveCost = 1;
			   add_edge(graph, i)
		     
		  for(int k=-1; k<1; k++) {
		     if ((col+k >= 0) && (col+k < colMax)) {
			switch (squares[row+j][col+k]){
			
	 }
      }
      
   }
   
   return 0;
}
