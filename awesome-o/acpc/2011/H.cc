// dynamic programming: best[n] = min length of string from s[0..n-1].
// Look for all possible suffixes of s[0..n-1] to see if we can compress that 
// suffix and concatenate with the best answer for the prefix. 

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

const int MAX_N = 200;

int numlen(int n)
{
  if (n < 10) return 1;
  if (n < 100) return 2;     
  if (n < 1000) return 3; 
  assert(false);   // don't really need this case for n <= 100
}

int best_power(const string &s, int start, int end)
{
  int n = end - start;
  int ans = n;                // you can always not do anything
  
  // there are some optimizations that I am not bothering...e.g. if
  // there is no base of length k*d for any k > 1 then there is no
  // base of length d either.
  for (int d = 1; d <= n/2; d++) {
    if (n % d != 0) continue;
    bool good = true;
    for (int i = start; i < start+d && good; i++) {
      for (int j = i+d; j < end && good; j += d) {
	good &= s[i] == s[j];
      }
    }
    if (good) {
      ans = min(ans, d + 2 + numlen(n/d));
    }
  }
  return ans;
}

void solve()
{
  string s;
  getline(cin, s);

  int n = s.length();
  s = string("#") + s;        // hack to make it 1-based

  int best[MAX_N+1];

  best[0] = 0;
  for (int n1 = 1; n1 <= n; n1++) {
    int index = 0;
    best[n1] = n1;               // don't compress it

    for (int i = 1; i <= n1; i++) {
      int t = best[i-1] + best_power(s, i, n1+1);
      best[n1] = min(best[n1], t);
      if (best[n1] == t) index = i;
    }
    cout << "best[" << n1 << "] = " << best[n1] << ", index = " << index << endl;
  }
  cout << best[n] << endl;
}

int main()
{
  int T;
  cin >> T;
  cin.ignore(1);
  while (T-- > 0) {
    solve();
  }

  return 0;
}
