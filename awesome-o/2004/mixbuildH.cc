#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_N = 10000;
const int MAX_LEN = 20;

struct Word {
  string word, sig;
  
  bool operator<(const Word &w) const
  {
    return sig < w.sig;
  }

  bool operator==(const Word &w) const
  {
    return sig == w.sig;
  }
};
  
Word words[MAX_LEN+1][MAX_N+1];
int n[MAX_LEN+1];
int longest;

void solve(ofstream &out)
{
  int len[MAX_LEN+1][MAX_N+1];
  int succ[MAX_LEN+1][MAX_N+1];
  int i, j, k;
  Word w;
  int best = 0, best_i = 0, best_j = 0;

  for (i = 1; i <= longest; i++) {
    sort(words[i], words[i] + n[i]);
  }

  for (j = 0; j < n[longest]; j++) {
    len[longest][j] = 1;
    succ[longest][j] = -1;
    if (1 > best) {
      best = 1;
      best_i = longest;
      best_j = j;
    }
  }

  for (i = longest-1; i >= 1; i--) {
    for (j = 0; j < n[i]; j++) {
      len[i][j] = 1;
      succ[i][j] = -1;

      for (k = 'a'; k <= 'z'; k++) {
	w.sig = words[i][j].sig;
	w.sig += static_cast<char>(k);
	sort(w.sig.begin(), w.sig.end());
	pair<Word *, Word *> p = equal_range(words[i+1], words[i+1]+n[i+1], w);
	if (p.first != p.second) {
	  int l = p.first - words[i+1];
	  int t = len[i+1][l] + 1;
	  if (t > len[i][j]) {
	    len[i][j] = t;
	    succ[i][j] = l;
	  }
	}
      }

      if (len[i][j] > best) {
	best = len[i][j];
	best_i = i;
	best_j = j;
      }
    }
  }

  while (best-- > 0) {
    out << words[best_i][best_j].word << endl;
    best_j = succ[best_i++][best_j];
  }

}

int main(void)
{
  ifstream in("mixbuild.in");
  ofstream out("mixbuild.out");
  string s;

  while (in >> s) {
    int l = s.length();
    if (l > longest) {
      longest = l;
    }
    words[l][n[l]].sig = words[l][n[l]].word = s;
    sort(words[l][n[l]].sig.begin(), words[l][n[l]].sig.end());
    n[l]++;
  }
  
  solve(out);

  return 0;
}
