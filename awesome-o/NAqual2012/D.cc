// Dynamic programming
//
// We do dynamic programming based on the subset of marks that still have to
// be considered (there are at most 2^n subsets).

#include <iostream>
#include <algorithm>

using namespace std;

int m, n;
int a[10];
int mark[101];

int ans[2000];

int compute(int S)
{
  // if it's already computed, just return it
  if (ans[S] >= 0) return ans[S];

  // if every mark is considered, answer is 0
  if (S == 0) return 0;

  // figure out the leftmost mark we still need to consider
  int first;
  for (int i = 0; i < n; i++) {
    if (S & (1 << i)) {
      first = i;
      break;
    }
  }

  // possibility one: first mark is a bike with large wheel, so the bike
  // doesn't contribute to any other mark
  ans[S] = compute(S - (1 << first)) + 1;

  // all other marks are potentially marked by the same bike (even
  // those that have been considered before, because multiple bikes
  // can leave a mark at the same spot)
  for (int k = 0; k < n; k++) {
    int dist = a[k] - a[first];
    if (dist < 0) dist = -dist;
    if (dist == 0) continue;

    // look forward and backward and make sure that all the marks this
    // bike can touch are indeed marked
    int newS = S;
    bool good = true;
    for (int mm = a[first] - dist; mm >= 0 && good; mm -= dist) {
      if (!mark[mm]) good = false;
      newS &= ~mark[mm];
    }
    
    for (int mm = a[first]; mm < m && good; mm += dist) {
      if (!mark[mm]) good = false;
      newS &= ~mark[mm];
    }
    if (good) {
      // remove the marks by this bike and recurse
      ans[S] = min(ans[S], 1+compute(newS));
    }
  }

  return ans[S];
}

int main()
{
  while (cin >> m >> n) {
    fill(mark, mark+m, 0);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    sort(a, a+n);
    for (int i = 0; i < n; i++) {
      mark[a[i]] = (1 << i);
    }

    fill(ans, ans+2000, -1);

    // consider all of the marks
    cout << compute((1 << n) - 1) << endl;
  }
  return 0;
}
