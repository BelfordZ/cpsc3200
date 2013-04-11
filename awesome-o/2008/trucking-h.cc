// Howard Cheng

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

ifstream in("trucking.in");
ofstream out("trucking.out");

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

struct Edge {
  Edge(int i=-1, int j=-1, int height=0, int length=0) {
    v1 = i;
    v2 = j;
    w = height;
    l = length;
  }
  bool operator<(const Edge& e) const { return w > e.w; }
  
  int v1, v2; 
  int w, l;      
};

int G[1000][1000];
Edge elist[500000];

int find_height(int n, int m, Edge elist[], int start, int end)
{
  UnionFind uf(n);

  sort(elist, elist+m);

  assert(start != end);
  int height = -1;
  int i;
  for (i = 0; i < m && uf.find(start) != uf.find(end); i++) {
    uf.merge(elist[i].v1, elist[i].v2);
    height = elist[i].w;
    G[elist[i].v1][elist[i].v2] = G[elist[i].v2][elist[i].v1] = elist[i].l;
  }
  for ( ; i < m && elist[i].w == height; i++) {
    G[elist[i].v1][elist[i].v2] = G[elist[i].v2][elist[i].v1] = elist[i].l;
  }

  if (uf.find(start) == uf.find(end)) {
    return height;
  } else {
    return -1;
  }
}

struct Node {
  int v;
  int d;

  Node(int vv = 0, int dd = 0) : v(vv), d(dd) { }
  bool operator<(const Node &n) const {
    return d > n.d;
  }
};

int dist(int n, int start, int end)
{
  bool visited[1000];
  priority_queue<Node> fringe;
  
  fill(visited, visited+n, false);
  fringe.push(Node(start, 0));
  while (true) {
    assert(!fringe.empty());
    Node next = fringe.top();
    fringe.pop();
    if (visited[next.v]) continue;
    if (next.v == end) {
      return next.d;
    }
    visited[next.v] = true;
    for (int i = 0; i < n; i++) {
      if (G[next.v][i] > 0 && !visited[i]) {
	fringe.push(Node(i, G[next.v][i] + next.d));
      }
    }
  }
  assert(0);
}

int main(void)
{
  int C, R;
  int case_num = 1;

  while (in >> C >> R && (C || R)) {
    for (int i = 0; i < C; i++) {
      for (int j = 0; j < C; j++) {
	G[i][j] = -1;
      }
    }
    for (int i = 0; i < R; i++) {
      int u, v, height, length;
      in >> u >> v >> height >> length;
      u--; v--;
      elist[i] = Edge(u, v, height, length);
    }

    int start, end, limit;
    in >> start >> end >> limit;
    start--; end--;
    for (int i = 0; i < R; i++) {
      if (elist[i].w == -1 || elist[i].w >= limit) {
	elist[i].w = limit;
      }
    }

    int max_height = find_height(C, R, elist, start, end);

    if (case_num > 1) {
      out << endl;
    }
    out << "Case " << case_num++ << ":" << endl;
    if (max_height < 0) {
      out << "cannot reach destination" << endl;
      continue;
    }
    out << "maximum height = " << max_height << endl;
    out << "length of shortest route = " << dist(C, start, end) << endl;
  }

  return 0;
}



