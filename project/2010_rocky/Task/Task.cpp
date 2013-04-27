//Problem 4885
//Solution By Bellman ford (implemented by Howard Cheng)
//  usage by Zach Belford

#include <iostream>
#include <climits>
#include <climits>
#include <cassert>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

//its an assignment problem!
//Its actually similar to the scheduling program I made for software eng!
//similar to the scheduling program I made for software eng. With
//              -Variables: The numeric time inputs Ti1 & Ti2
//              -Domain: Tasks to be assigned Task[1...n]
//              -Constraints: Time:{Task[l]} < numeric input+ Time:{Task[k]}
//                      (and) Time:{Task[l]} < numeric input-/+ Time:{Task[k]}

//I was thinking of using constraint programming,
//but then saw just constructing it as a weighted graph and finding
//shortest path to a certain tree depth. In this case our depth is determined
//by the number of tasks, where our breadth depends on our method here.
//the simplest approach seems to be building a graph with vertices
//on each Task bound by a constraint to another. The edges in this case
//would then be weighted by the best choice (here its a smallest number
//of time a task may begin) of its neighbors. Anyways.. here goes nothin!

using namespace std;

/*
 * Bellman-Ford Shortest Path Algorithm
 *
 * Author: Howard Cheng
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
 * Note: the Bellman-Ford algorithm has complexity O(n^3), but it works even
 *       when edges have negative weights.  As long as there are no negative
 *       cycles the computed results are correct.
 *
 *       We can make this O(n*m) if we use an adjacency list representation.
 *
 *       This works for directed graphs too.
 *
 *       You can use this to detect negative cycles too.  See code.
 *
 */
// can only have max 100 tasks
// 1 base index, so add 1
const int MAX_NODES = 100+1;
const int DISCONNECT = INT_MAX;
bool done = false;

template <class T>
bool from_string(T& t, 
                 const std::string& s, 
                 std::ios_base& (*f)(std::ios_base&))
{
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}

/* assume that D and P have been allocated */
void bellmanford(int graph[MAX_NODES][MAX_NODES], int n, int src,
		 int D[], int P[])
{
  int v, w, k;
  
  for (v = 0; v < n; v++) {
    D[v] = INT_MAX;
    P[v] = -1;
  }
  D[src] = 0;

  for (k = 0; k < n-1; k++) {
    for (v = 0; v < n; v++) {
      for (w = 0; w < n; w++) {
	if (graph[v][w] != DISCONNECT && D[v] != INT_MAX) {
	  if (D[w] == INT_MAX || D[w] > D[v] + graph[v][w]) {
	    D[w] = D[v] + graph[v][w];
	    P[w] = v;
	  } else if (D[w] == D[v] + graph[v][w]) {
	    /* do some tie-breaking here */
	  }
	}
      }
    }
  }

  /* the following loop is used only to detect negative cycles, not */
  /* needed if you don't care about this                            */
  for (v = 0; v < n; v++) {
    for (w = 0; w < n; w++) {
      if (graph[v][w] != DISCONNECT && D[v] != INT_MAX) {
        if (D[w] == INT_MAX || D[w] > D[v] + graph[v][w]) {
	  /* if we get here then there is a negative cycle somewhere */
	  /* on the path from src to                                 */
	   cout << "Impossible" << endl; //complete search done.. Peeeace!
	   done = true;
	}
      }
    }
  }

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
/*
int main(void)
{
  // clear graph
  for (i = 0; i < MAX_NODES; i++) {
    for (j = 0; j < MAX_NODES; j++) {
      graph[i][j] = DISCONNECT;
    }
  }

  // read graph
  cin >> i >> j >> w;
  while (!(i == -1 && j == -1)) {
    assert(0 <= i && i < MAX_NODES && 0 <= j && j < MAX_NODES);
    graph[i][j] = graph[j][i] = w;
    cin >> i >> j >> w;
  }

  for (i = 0; i < MAX_NODES; i++) {
    bellmanford(graph, MAX_NODES, i, D[i], P[i]);
  }

  // do queries
  cin >> i >> j;
  while (!(i == -1 && j == -1)) {
    assert(0 <= i && i < MAX_NODES && 0 <= j && j < MAX_NODES);
    cout << i << " " << j << ": " << D[i][j] << endl;
    for (m = j; m != -1; m = P[i][m]) {
      cout << " " << m;
    }
    cout << endl;
    num = get_path(j, P[i], path);
    for (m = 0; m < num; m++) {
      cout << " " << path[m];
    }
    cout << endl;
    cin >> i >> j;
  }

  return 0;
}
*/
struct edge {
      int A, ti, tj, opCode;
}constraints[10000]; // n^2 max edges?

string crap = "";

int main() {
   // time for some super fun string processing
   int numTasks = 0, numConstraints = 0;
   while (cin>>numTasks>>numConstraints && numTasks !=0) {
      int m, w, num;
   int graph[MAX_NODES][MAX_NODES];
   int P[MAX_NODES], D[MAX_NODES];
   int path[MAX_NODES];
   for (int i = 0; i < MAX_NODES; i++) 
      for (int j = 0; j < MAX_NODES; j++) 
	 graph[i][j] = DISCONNECT;

   //cout << "NumTasks: " << numTasks << ", NumConstraints: " << numConstraints << endl;

   //read in the constraints.
   for (int i=0; i<numConstraints; i++) {
      // time for some super fun string processing
      //cout << "The " << i << "th constraint:" << endl;
      string operation, line, lineBuf;
      cin >> crap >> lineBuf >> crap;//pull out 'task' and 'starts', saves taskNum
      from_string<int>(constraints[i].ti, lineBuf, std::dec);
      //cout << "---->Ti: " << lineBuf << endl;

      cin >> lineBuf; //saves 'at' or 'within'
      //cout << "---->opCode: " << lineBuf << endl;
      
      if (lineBuf == "at") { // we know its op0
	 constraints[i].opCode = 0;
	 cin >> crap;//pull out 'least'
	 
      }else if (lineBuf == "within"){//its op1
	 constraints[i].opCode = 1;
      }
      cin >> lineBuf >> crap;
      //cout << "---->A: " << lineBuf << " " << crap << endl;
      cin >> crap >> crap >> crap;//get A, toss 'minutes of/later the/than task/starting
      from_string<int>(constraints[i].A, lineBuf, std::dec);
      //istringstream ( lineBuf ) >> constraints[i].A;// cast it
      if (constraints[i].opCode) { //has 3 more crap words
	 cin >> crap >> crap >> crap;
      }
      cin >> lineBuf;
      //cout << "---->Tj: " << lineBuf << endl;
      from_string<int>(constraints[i].tj, lineBuf, std::dec);
   }

   //build graph
   for (int i=0; i<numConstraints; i++) {
      edge x = constraints[i];
      //cout << "switch " << i << endl;
      switch (x.opCode) {
	    // the 'minutes later than...' is represented by an edge from
	    // ti to tj. The weight of the path, since 'A minutes
	    // later', is the minute difference that must exists, thus -A.
	 
	    // BUT, if its already scheduled with a better time, then just remain
	    // ti must be time=A before tj in the connection from ti to tj
	 case 0:
	    if (graph[x.ti][x.tj] > 0-x.A) {
	       graph[x.ti][x.tj] = 0-x.A;;
	    }
	    else{}
	    break;

	    // 'of the starting time' is rep as an edge from ti -> tj. It 
	    // enforces the constraint that the starting time difference of
	    // ti and tj must be A, and tj must start first.
	    // so, we want the most strict constraint between being A minutes later,
	    // and ...
	 case 1:
	    if (graph[x.tj][x.ti] > x.A){
	       graph[x.tj][x.ti] = x.A;
	       //cout << "tj, ti = " << 0 << endl;
	    } 
	    if (graph[x.ti][x.tj] > 0) {
	       graph[x.ti][x.tj] = 0;
	       //cout << "ti, tj = " << x.A << endl;
	    } 
	    break;
      }
      //cout << "Graph @ ti,tj: "<< graph[x.ti][x.tj] << endl;
      //for (int y=0; y<numTasks; y++) {
      if(!done) {
	 bellmanford(graph, numTasks+1, 0, D, P);
	 int adj = *min_element(D+1, D+numTasks+1);
	 for (int r = 1; r <= numTasks; r++) {
	    cout << D[i] - adj + 1;
	    if (i<numTasks) cout << " " ;
	    else cout << endl;
	 }
      }
      break;
	 //}
      //cout << D[i] - adj + 1 << endl;
      // for (int e=1; e<numTasks+1; e++){
      // 	 for(int o=0; o<numTasks+1; o++) {
      // 	    cout << D[e]-adj+1 <<  " " << adj << endl;
      // 	 }
      // }
   }
   }
   return 0;
}
