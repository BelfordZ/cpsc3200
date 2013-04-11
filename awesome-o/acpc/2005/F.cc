#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX_N = 5000;
const int MAX_K = 1000;
const int MAX_L = 500;

int n, k, l;
pair<int,int> edge[2*MAX_N-2];
pair<int,int> G[MAX_N];    /* first = start of entries
                              second = one past the end */

#define DEBUG 

struct Ant {
  int location;
  int times;
  
  void init(int loc) {
    location = loc;
    times = 0;
  }
};

ostream &operator<<(ostream &os, const Ant &ant)
{
  return os << ant.location+1 << ' ' << ant.times;
}

Ant ant[MAX_K];


int read_graph(void)
{
  cin >> n;
  if (!n) {
    return 0;
  }

  int u, v, j;
  j = 0;
  for (int i = 0; i < n-1; i++) {
    cin >> u >> v;
    u--; v--;
    edge[j++] = make_pair<int,int>(u, v);
    edge[j++] = make_pair<int,int>(v, u);
  }
  sort(edge, edge + 2*(n-1));
  
  j = 0;
  for (int i = 0; i < n; i++) {
    G[i].first = j;
    while (j < 2*(n-1) && edge[j].first == i)
      j++;
    G[i].second = j;
  }

  cin >> k;
  for (int i = 0; i < k; i++) {
    cin >> j;
    j--;
    ant[i].init(j);
  }
  return 1;
}

void DFS1(int u, int parent, int dist, int *Du, int *Pu, 
	  int *mark_t, int *mark_id, int *ant_mark, int *path_len)
{
  if (ant_mark[u] < 0) {
    mark_t[u] = mark_id[u] = -1;
  } else {
    mark_t[u] = path_len[ant_mark[u]] = 0;
    mark_id[u] = ant_mark[u];
  }
  Du[u] = dist;
  Pu[u] = parent;
  
  for (int i = G[u].first; i != G[u].second; ++i) {
    int v = edge[i].second;
    if (Du[v] < 0) {
      DFS1(v, u, dist+1, Du, Pu, mark_t, mark_id, ant_mark, path_len);

      // no ants in the subtree, do nothing
      if (mark_t[v] == -1) continue;

      // subtree has a closer ant
      if (mark_t[u] == -1) {
	mark_t[u] = mark_t[v]+1;
	mark_id[u] = mark_id[v];
	path_len[mark_id[u]]++;
      } else if (mark_t[v]+1 < mark_t[u]) {
	// need to adjust previous best
	path_len[mark_id[u]] = mark_t[v]+1;
	mark_t[u] = mark_t[v]+1;
	mark_id[u] = mark_id[v];
	path_len[mark_id[u]]++;
      } else if (mark_t[v]+1 == mark_t[u] && mark_id[v] < mark_id[u]) {
	// need to adjust previous
	path_len[mark_id[u]] = mark_t[v];
	mark_t[u] = mark_t[v]+1;
	mark_id[u] = mark_id[v];
	path_len[mark_id[u]]++;
      }
      
      // subtree has a further ant
    }
  }
}

void solve_case(void)
{
  int l, bug;
  int Dbug[MAX_N], Pbug[MAX_N];
  int mark_t[MAX_N], mark_id[MAX_N], ant_mark[MAX_N];
  int path_len[MAX_K];

  cin >> l;

  while (l-- > 0) {
    cin >> bug;

#ifdef DEBUG
    cout << "Bug = " << bug << endl;
#endif
    bug--;
    fill(Dbug, Dbug+n, -1);
    fill(mark_t, mark_t+n, -1);
    fill(mark_id, mark_id+n, -1);
    fill(ant_mark, ant_mark+n, -1);

    for (int i = 0; i < k; i++) {
      ant_mark[ant[i].location] = i;
    }

    DFS1(bug, -1, 0, Dbug, Pbug, mark_t, mark_id, ant_mark);

#ifdef DEBUG
    cout << "  dist: ";
    for (int i = 0; i < k; i++) {
      cout << Dbug[ant[i].location] << " ";
    }
    cout << endl;
    cout << "  mark_t : ";
    for (int i = 0; i < n; i++) {
      cout << mark_t[i] << " ";
    }
    cout << endl;
    cout << "  mark_id : ";
    for (int i = 0; i < n; i++) {
      cout << mark_id[i] << " ";
    }
    cout << endl;
#endif

    fill(path_len, path_len+k, 0);
    for (int i = 0; i < n; i++) {
      if (mark_t[i] > 0) {
	path_len[mark_id[i]] = max(path_len[mark_id[i]], mark_t[i]);
      }
    }

#ifdef DEBUG
    cout << "  path_len: ";
    for (int i = 0; i < k; i++) {
      cout << path_len[i] << " ";
    }
    cout << endl;
#endif

    for (int i = 0; i < k; i++) {
      for (int j = 0; j < path_len[i]; j++) {
	ant[i].location = Pbug[ant[i].location];
      }
      if (ant[i].location == bug) {
	ant[i].times++;
      }
    }
    

#ifdef DEBUG
    for (int i = 0; i < k; i++) {
      cout << ant[i] << endl;
    }
    cout << "------------" << endl;
#endif
  }
  
  for (int i = 0; i < k; i++) {
    cout << ant[i] << endl;
  }
}

int main(void)
{
  while (read_graph()) {
    solve_case();
  }
  return 0;
}
