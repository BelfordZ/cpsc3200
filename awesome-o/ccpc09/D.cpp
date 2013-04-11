// try all permutation of M objects chosen from N objects.
//
// Since N = 8 is so small, we will generate all N! permutations and
// just use the first M items as the chosen list (there will be a
// factor of (N-M)! wasted work because many of the N! permutations
// will have the first M objects in the same order, but N is small).
//
// we can use next_permutation to generate permutation in lexicographical
// order and compute the best one.

#include <iostream>
#include <algorithm>

using namespace std;

int abs(int x)
{
  return (x > 0) ? x : -x;
}

// shortest distance between every pair of locations
int D[8][8];

// given a permutation, compute the distance to visit the first M locations
int dist(int perm[], int M)
{
  int d = 0;
  for (int i = 1; i < M; i++) {
    d += D[perm[i-1]][perm[i]];
  }
  return d;
}

int main(void)
{
  int T;

  cin >> T;
  while (T-- > 0) {
    int N, M;
    cin >> N >> M;

    int x[8], y[8];
    

    for (int i = 0; i < N; i++) {
      cin >> x[i] >> y[i];
    }
    
    // compute all pairwise distances
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
	D[i][j] = abs(x[i] - x[j]) + abs(y[i] - y[j]);
      }
    }

    int perm[8], best_perm[8];

    // initialize the lexicographically smallest permutation
    for (int i = 0; i < N; i++) {
      perm[i] = i;
    }
    int best = dist(perm, M);
    copy(perm, perm+M, best_perm);

    // generate the next ones and replace the best values if appropriate
    while (next_permutation(perm, perm+N)) {
      int temp = dist(perm, M);
      if (temp < best) {
	best = temp;
	copy(perm, perm+M, best_perm);
      }
    }
    for (int i = 0; i < M; i++) {
      if (i) cout << ' ';
      cout << best_perm[i];
    }
    cout << endl;
  }
  return 0;
}
