#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <cassert>
#include <map>
#include <sstream>

using namespace std;

struct Edge;
typedef list<Edge>::iterator EdgeIter;

struct Edge {
   int to;
   int cap;
   int flow;
   bool is_real;
   EdgeIter partner;
   
   Edge(int t, int c, bool real = true)
      : to(t), cap(c), flow(0), is_real(real)
   {};
   
   int residual() const
   {
      return cap - flow;
   }
};

struct Graph {
   list<Edge> *nbr;
   int num_nodes;
   Graph(int n)
      : num_nodes(n)
   {
      nbr = new list<Edge>[num_nodes];
   }
   
   ~Graph()
   {
      delete[] nbr;
   }
   
   // note: this routine adds an edge to the graph with the specified capacity,
   // as well as a residual edge.  There is no check on duplicate edge, so it
   // is possible to add multiple edges (and residual edges) between two
   // vertices
   void add_edge(int u, int v, int cap)
   {
      nbr[u].push_front(Edge(v, cap));
      nbr[v].push_front(Edge(u, 0, false));
      nbr[v].begin()->partner = nbr[u].begin();
      nbr[u].begin()->partner = nbr[v].begin();
   }
};

void push_path(Graph &G, int s, int t, const vector<EdgeIter> &path, int flow)
{
   for (int i = 0; s != t; i++) {
      if (path[i]->is_real) {
	 path[i]->flow += flow;
	 path[i]->partner->cap += flow;
      } else {
	 path[i]->cap -= flow;
	 path[i]->partner->flow -= flow;
      }
      s = path[i]->to;
   }
}

// the path is stored in a peculiar way for efficiency: path[i] is the
// i-th edge taken in the path.
int augmenting_path(const Graph &G, int s, int t, vector<EdgeIter> &path,
		    vector<bool> &visited, int step = 0)
{
   if (s == t) {
      return -1;
   }
   for (EdgeIter it = G.nbr[s].begin(); it != G.nbr[s].end(); ++it) {
      int v = it->to;
      if (it->residual() > 0 && !visited[v]) {
	 path[step] = it;
	 visited[v] = true;
	 int flow = augmenting_path(G, v, t, path, visited, step+1);
	 if (flow == -1) {
	    return it->residual();
	 } else if (flow > 0) {
	    return min(flow, it->residual());
	 }
      }
   }
   return 0;
}
// note that the graph is modified
int network_flow(Graph &G, int s, int t)
{
   vector<bool> visited(G.num_nodes);
   vector<EdgeIter> path(G.num_nodes);
   int flow = 0, f;
   
   do {
      fill(visited.begin(), visited.end(), false);
      if ((f = augmenting_path(G, s, t, path, visited)) > 0) {
	 push_path(G, s, t, path, f);
	 flow += f;
      }
   } while (f > 0);
   
   return flow;
}

int main(void)
{
   Graph G(10000);
   int s, t, u, v, cap, flow;

   int numTests;
   cin >> numTests;

   map<string, int> clubID;
   map<string, int> partyID;
   string memberNames[1000];
   string clubNames[10000];
   vector<int> clubsToMembers[1000];
   int party[1000];
   
   string line;
   getline(cin, line);
   getline(cin, line);

   for (int i=0; i<numTests; i++) {
      int c, m, p; //curr num of clubs, members, parties
      c = m = p = 0;

      clubID.clear();
      partyID.clear();

      while (getline(cin, line) && line != "") {
	 stringstream iss(line);
	 string name, part, club;
	 iss >> name >> part;
	 memberNames[m] = name;

	 if (partyID.find(part) == partyID.end()) {
	    p += 1;
	    partyID[part] = p;
	 }
	 party[m] = partyID[part];

	 while(iss >> club) {
	    if(clubID.find(club) == clubID.end()) {
	       clubID[club] = c;
	       clubNames[c] = club;
	       c++;
	    }
	    clubsToMembers[m].push_back(clubID[club]);
	 }
	 m++; // finally we increment the number of Members
      }
      for (int i=0; i<m; i++) {
	 G.add_edge(c+i+1, c+m+party[i]+1, 1);
      }
      for (int i=0; i<p; i++) {
	 G.add_edge(c+m+i+1, c+m+p+1, (c-1)/2);
      }
      for (int i=0; i<c;) {
	 G.add_edge(0, i++, 1);
      }

      for (int i = 0; i < m; i++) {
	 for (int j=0; j<clubsToMembers[i].size()-1; j++) {
	    int k = clubsToMembers[i][j];
	    G.add_edge(k+1, c+i+1, 1);
	 }
      }

      if(network_flow(G, 0, c+m+p+1) != c) {
	 cout<<"Impossible."<<endl;
      }
      /*else {
	 int edge = G.E;
	 
	 for(int e = 0;e<E;e += 2){
	    int u = G.to[e^1]-1, v = G.to[e]-1-N3;
            
	    if(G.cap[e]==0 && u>=0 && u<N3 && v>=0 && v<N1)
	       cout<<personName[v]<<" "<<clubName[u]<<endl;
	 }
	 }
      */
   }
   
   return 0;
}
