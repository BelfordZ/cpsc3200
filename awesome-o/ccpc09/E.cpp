#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void solve()
{
  int N, M;

  cin >> N >> M;

  // read in the title and build the acronym
  string acro;
  for (int i = 0; i < N; i++) {
    string word;
    cin >> word;
    acro += word[0];
  }

  // read in list of words and sort it
  vector<string> list(M);
  for (int i = 0; i < M; i++) {
    cin >> list[i];
  }
  sort(list.begin(), list.end());

  // see which letters are present
  bool present[256];
  int count = 0;
  fill(present, present+256, false);
  for (string::size_type i = 0; i < acro.length(); i++) {
    if (!present[acro[i]]) count++;
    present[acro[i]] = true;
  }
  if (count != 2) {
    cout << "No cryptic-friendly acronym" << endl;
    return;
  }
  
  // figure out how to flip between the two characters
  char ch1 = '.', ch2 = '.';
  for (int i = 'A'; i <= 'Z'; i++) {
    if (!present[i]) continue;
    if (ch1 == '.') {
      ch1 = i;
    } else {
      ch2 = i;
    }
  }
  char change[256];
  change[ch1] = ch2;
  change[ch2] = ch1;
  
  // now build the fragment, only using each word once
  string fragment;
  vector<bool> used(M);
  fill(used.begin(), used.end(), false);

  for (string::size_type j = 0; j < acro.length(); j++) {
    char target = change[acro[j]];

    // look for the first unused word with the right first letter
    int i = 0;
    while (i < M && (used[i] || list[i][0] != target)) {
      i++;
    }

    // not found
    if (i >= M) {
      cout << "No cryptic-ordered fragment" << endl;
      return;
    }
    if (j) {
      fragment += " ";
    }
    fragment += list[i];
    used[i] = true;
  }
  cout << fragment << endl;

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
