#include <string>
#include <iostream>

using namespace std;

// we store the keyboard as an array of strings
const string keyboard[3] = {
  "QWERTYUIOP",
  "ASDFGHJKL",
  "ZXCVBNM"
};

int abs(int a)
{
  return (a > 0) ? a : -a;
}

int main(void)
{
  // we map each character into the rows and columns
  int row[256], col[256];

  for (char c = 'A'; c <= 'Z'; c++) {
    for (int i = 0; i < 3; i++) {
      string::size_type j = keyboard[i].find(c);
      if (j != string::npos) {
	row[c] = i;
	col[c] = j;
      }
    }
  }

  int T;
  cin >> T;

  string line;
  getline(cin, line);
  while (T-- > 0) {
    getline(cin, line);

    // just remember to keep track of the last character
    int ans = 0;
    int prev_r = row['E'];
    int prev_c = col['E'];
    for (string::size_type i = 0; i < line.length(); i++) {
      if (line[i] == ' ') {
	ans += 5;
	continue;
      }
      ans += 1 + 2*abs(row[line[i]] - prev_r) + 2*abs(col[line[i]] - prev_c);
      prev_r = row[line[i]];
      prev_c = col[line[i]];
    }
    cout << ans << endl;
  }

  return 0;
}
