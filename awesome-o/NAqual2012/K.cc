// there isn't much to this problem.  Just do it.

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
  string line[100];
  int n = 0;

  while (getline(cin, line[n])) n++;

  size_t N = 0;
  for (int i = 0; i < n; i++) {
    N = max(N, line[i].length());
  }

  int ans = 0;
  for (int i = 0; i < n-1; i++) {
    ans += (N - line[i].length()) * (N - line[i].length());
  }
  cout << ans << endl;

  return 0;
}
