#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int MAX_NODES = 10000;
const int PEA_COST = 100;
const int SPLIT_COST = 175;
const int STAR_COST = 500;

int n, m;
vector<int> adj[MAX_NODES];

// assume tree is connected, vertices are 0-based.

// best cost to cover the entire subtree rooted at u, and may cover the edge
//    to the parent of u (but not necessarily)
// best cost to cover the entire subtree rooted at u PLUS the edge to parent
//    of u.
int best[MAX_NODES], best_parent[MAX_NODES];

void compute(int root, int parent = -1)
{
  int deg = adj[root].size();
  if (deg == 1 && parent != -1) {
    // leaf node
    best[root] = 0;
    best_parent[root] = PEA_COST;      // should just shoot up
    return;
  }

  // some preprocessing
  int sum = 0;
  int sum_parent = 0;
  int best1, best2;     // the costs of best 2 subtrees to not link the parent
  best1 = best2 = INT_MAX;  // best1 <= best2

  for (int i = 0; i < deg; i++) {
    int v = adj[root][i];
    if (v == parent) continue;
    compute(v, root);
    sum += best[v];
    sum_parent += best_parent[v];
    
    int t = best[v] - best_parent[v];
    if (t < best1) {
      best2 = best1;
      best1 = t;
    } else if (t < best2) {
      best2 = t;
    }
  }
  
  // do best_parent[root] first: must plant something
  
  // try the star
  best_parent[root] = STAR_COST + sum;

  // try the peashooter: must shoot to parent
  best_parent[root] = min(best_parent[root], PEA_COST + sum_parent);
  
  // try the split pea: must shoot to parent and one child --- the child v
  // where best[v] - best_parent[v] is minimum
  best_parent[root] = min(best_parent[root], SPLIT_COST + sum_parent + best1);
  

  // now do best[root]

  // try not to put anything
  best[root] = sum_parent;

  // try to use a peashooter: must cover one of the subtrees
  best[root] = min(best[root], sum_parent + best1 + PEA_COST);

  // try to use a split pea: must cover two of the subtrees
  if ((parent == -1 && deg >= 2) || (parent >= 0 && deg >= 3)) {
    best[root] = min(best[root], sum_parent + best1 + best2 + SPLIT_COST);
  }

  // try star too: it may shoot to parent but we don't care
  best[root] = min(best[root], sum + STAR_COST);

  // it may be better to cover the parent anyway
  best[root] = min(best[root], best_parent[root]);
}

void solve()
{
  cin >> n;
  m = n-1;
  for (int i = 0; i < n; i++) {		       
    adj[i].clear();
  }

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  compute(0);
  cout << "$" << best[0] << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    solve();
  }
  return 0;
}
