// create disjoint sets, each set representing a state.
// for each disjoint set, create the shortest path that connects all vertices.
// find the shortest path that connects these disjoint sets

/*
 * Implementation of Kruskal's Minimum Spanning Tree Algorithm
 *
 * Author: Howard Cheng
 *
 * This is a routine to find the minimum spanning tree.  It takes as
 * input:
 *
 *      n: number of vertices
 *      m: number of edges
 *  elist: an array of edges (if (u,v) is in the list, there is no need
 *         for (v,u) to be in, but it wouldn't hurt, as long as the weights
 *         are the same).
 *
 * The following are returned:
 *
 *  index: an array of indices that shows which edges from elist are in
 *         the minimum spanning tree.  It is assumed that its size is at
 *         least n-1.
 *   size: the number of edges selected in "index".  If this is not
 *         n-1, the graph is not connected and we have a "minimum
 *         spanning forest."
 *
 * The weight of the MST is returned as the function return value.
 * 
 * The run time of the algorithm is O(m log m).
 *
 * Note: the elements of elist may be reordered.
 *
 * Modified by Rex Forsyth using C++  Aug 28, 2003
 * This version defines the unionfind and edge as classes and  provides
 * constructors. The edge class overloads the < operator. So the sort does
 * not use a  * cmp function. It uses dynamic arrays.
 */

#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <sstream>
using namespace std;

class UnionFind
{
      struct UF { int p; int rank; };

   public:
      UnionFind(int n) {          // constructor
	 howMany = n;
	 uf = new UF[howMany];
	 for (int i = 0; i < howMany; i++) {
	    uf[i].p = i;
	    uf[i].rank = 0;
	 }
      }

      ~UnionFind() {
         delete[] uf;
      }

      int find(int x) { return find(uf,x); }        // for client use
      
      bool merge(int x, int y) {
	 int res1, res2;
	 res1 = find(uf, x);
	 res2 = find(uf, y);
	 if (res1 != res2) {
	    if (uf[res1].rank > uf[res2].rank) {
	       uf[res2].p = res1;
	    }
	    else {
	       uf[res1].p = res2;
	       if (uf[res1].rank == uf[res2].rank) {
		  uf[res2].rank++;
	       }
	    }
	    return true;
	 }
	 return false;
      }
      
   private:
      int howMany;
      UF* uf;

      int find(UF uf[], int x) {             // for internal use
	 if (uf[x].p != x) {
	    uf[x].p = find(uf, uf[x].p);
	 }
	 return uf[x].p;
      }
};

class Edge {

   public:
      Edge(int i=-1, int j=-1, double weight=0) {
	 v1 = i;
	 v2 = j;
	 w = weight;
      }
      bool operator<(const Edge& e) const { return w < e.w; }

      int v1, v2;          /* two endpoints of edge                */
      double w;            /* weight, can be double instead of int */
};


double mst(int n, int m, Edge elist[], int index[], int& size)
{
  UnionFind uf(n);

  sort(elist, elist+m);

  double w = 0.0;
  size = 0;
  for (int i = 0; i < m && size < n-1; i++) {
    int c1 = uf.find(elist[i].v1);
    int c2 = uf.find(elist[i].v2);
    if (c1 != c2) {
      index[size++] = i;
      w += elist[i].w;
      uf.merge(c1, c2);
    }
  }

  return w;
}

int main(void)
{
   int numTestCases;
   cin >> numTestCases;

   for (int a=0; a<numTestCases; a++) {
      int numVertices, stateThresh;
      cin >> numVertices >> stateThresh;
      
      int x[numVertices], y[numVertices];
      Edge* vertices = new Edge[numVertices*numVertices];
      for (int i = 0; i < numVertices; i++)  cin >> x[i] >> y[i];
      
      int k = 0;      
      for (int i=0; i<numVertices; i++) {
	 for (int j=0; j<numVertices; j++) {
	    vertices[k++] = Edge(i,j, hypot(x[i]-x[j], y[i]-y[j]) );
	 }
      }
      
      int* index = new int[numVertices];
      int t=0;
      mst(numVertices, k, vertices, index, t);
      
      
      int roadSum = 0;
      int railSum = 0;
      int numStates = 1;
      for(int m=0; m<t; m++) {
	 if ( floor(pow(vertices[index[m]].w, 2)+0.5) <= pow(stateThresh, 2) ) {
	    roadSum += vertices[index[m]].w;
	 }
	 else {
	    numStates++;
	    railSum += vertices[index[m]].w;
	 }
      }
      cout << "Case #" << a+1 << ": " << numStates << " " << roadSum << " " << railSum << endl;
   }
   
   return 0;
}
