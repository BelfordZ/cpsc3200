// Solution to Stock Prices
//
// Howard Cheng
// Aug 24, 2011
//
// The idea: sort the whole thing.
//

#include <iostream>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

typedef pair<int,int> pii;

pii *A;

bool solve(int id)
{
  int n, k1, k2;
  cin >> n >> k1 >> k2;
  if (!n && !k1 && !k2) {
    return false;
  }
  cout << "Case " << id << endl;

  for (int d = 1; d <= n; d++) {
    cin >> A[d-1].first;
    A[d-1].second = d;
  }

  sort(A, A+n);
  
  int sA[100], lA[100];
  for (int i = 0; i < k1; i++) {
    sA[i] = A[i].second;
  }
  sort(sA, sA+k1);
  for (int i = 0; i < k1; i++) {
    if (i) cout << ' ';
    cout << sA[i];
  }
  cout << endl;

  for (int i = 0; i < k2; i++) {
    lA[i] = A[n-1-i].second;
  }
  sort(lA, lA+k2);
  for (int i = k2-1; i >= 0; i--) {
    cout << lA[i];
    if (i > 0) cout << ' ';
  }
  cout << endl;

  return true;
}

int main()
{
  A = new pii[10000000];
  int id = 1;
  while (solve(id++))
    ;
  return 0;
}
