// Each cycle must consist of a subset (of size >= 2) of the vertices as well
// as an order.  So we just try all possible subsets, and for each subset of
// size k try all possible (k-1)! order.  It's (k-1)! instead of k! because
// we are considering the permutations in a circle (fix the first one).
//
// For each subset-permutation, just follow along the permutation to make
// sure all the edges are there.


#include <iostream>
#include <algorithm>


using namespace std;

int main()
{
  int n, m;
  cin >> n >> m;

  int G[9][9];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      G[i][j] = 0;
    }
  }
  
  for (int i = 0; i < m; i++) {
    int s, t;
    cin >> s >> t;
    G[s][t] = 1;
  }

  int ans = 0;

  // S is a bit mask for the subset we choose
  for (int S = 1; S < (1 << n); S++) {
    int perm[9];
    int num = 0;
    for (int i = 0; i < n; i++) {
      if (S & (1 << i)) perm[num++] = i;
    }
    if (num == 1) continue;
    do {
      bool good = G[perm[num-1]][perm[0]];
      for (int i = 0; i < num-1 && good; i++) {
	good &= G[perm[i]][perm[i+1]];
      }
      if (good) ans++;
    } while (next_permutation(perm+1, perm+num));
  }
  cout << ans << endl;
  
  return 0;
}
