#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_N = 1000;

struct Word {
  string w;
  int index;
  int len;
};

bool cmp_word(const Word &x, const Word &y) {
  return x.w < y.w;
}

bool cmp_index(const Word &x, const Word &y) {
  return x.index < y.index;
}

ostream &operator<<(ostream &os, const Word &x)
{
  return os << x.w << " " << x.w.substr(0, x.len);
}

int common(const string &s1, const string &s2)
{
  unsigned int i;
  for (i = 0; i < s1.length() && i < s2.length() && s1[i] == s2[i]; i++) ;
  return i;
}

int max(int a, int b)
{
  return (a > b) ? a : b;
}

int min(int a, int b)
{
  return (a < b) ? a : b;
}

Word word[MAX_N];
int n;

int main(void)
{
  string s, prev, next;
  ifstream in("prefix.in");
  ofstream out("prefix.out");

  while (in >> s) {
    word[n].w = s;
    word[n].index = n;
    n++;
  }
  sort(word, word+n, cmp_word);
  
  for (int i = 0; i < n; i++) {
    prev = (i) ? word[i-1].w : "";
    next = (i < n-1) ? word[i+1].w : "";
    int c1 = common(prev, word[i].w);
    int c2 = common(next, word[i].w);
    word[i].len = min(max(c1,c2) + 1, word[i].w.length());
  }
  sort(word, word+n, cmp_index);
  for (int i = 0; i < n; i++) {
    out << word[i] << endl;
  }
  return 0;
}
