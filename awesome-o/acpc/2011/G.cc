// just simulate.
//
// if there are x rounds of best-of-3, and y rounds of best-of-5,
// then x+y = M and 2*x+3*y = max victories by winner.
//


#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <cassert>

using namespace std;

typedef pair<string, int> psi;

void solve()
{
  int M;
  cin >> M;

  int max_score = 0;
  psi scores[1024];
  int num = (1 << M);
  for (int i = 0; i < num; i++) {
    cin >> scores[i].first >> scores[i].second;
    max_score = max(max_score, scores[i].second);
  }
  sort(scores, scores + num, greater<psi>());

  int best3 = 3*M - max_score;
  assert(0 <= best3 && best3 <= M);

  
  bool used[1024];
  fill(used, used+num, false);

  string ans[1024];
  int k = 0;
  for (int i = 0; i < M; i++) {
    // eliminate
    int count = 0;

    for (int j = 0; j < num; j++) {
      if (used[j]) continue;

      int towin = (i < best3) ? 2 : 3;
      if (scores[j].second < towin) {
	ans[k++] = scores[j].first;
	used[j] = true;
	count++;
      } else {
	scores[j].second -= towin;
      }
    }
    assert(count == (1 << (M - i))/2);
  }

  for (int j = 0; j < num; j++) {
    if (!used[j]) {
      ans[k++] = scores[j].first;
    }
  }
  
  for (int i = num-1; i >= 0; i--) {
    cout << ans[i] << endl;
  }
}

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    solve();
  }

  return 0;
}
