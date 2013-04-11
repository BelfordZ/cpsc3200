#include <iostream>
#include <string>

using namespace std;

const int MAX_LENGTH = 250;

bool solvable(const string &line, int table[MAX_LENGTH][MAX_LENGTH+1],
	      int start, int len)
{
  if (table[start][len] != -1) {
    return table[start][len];
  }

  if (len == 0) {
    return (table[start][len] = true);
  }
  
  // there are three nontrivial cases for a string s to be solvable:
  //
  //  1. s = xy
  //  2. s = AxA
  //  3. s = AxAyA
  //
  // where x, y are solvable and A is any letter

  // case 1
  for (int xlen = 1; xlen <= len-1; xlen++) {
    if (solvable(line, table, start, xlen) &&
	solvable(line, table, start+xlen, len-xlen)) {
      return (table[start][len] = true);
    }
  }

  // case 2 & 3
  if (len >= 2 && line[start] == line[start+len-1]) {

    // case 2
    if (solvable(line, table, start+1, len-2)) {
      return (table[start][len] = true);
    }

    // case 3
    for (int mid = start+1; mid <= start+len-2; mid++) {
      if (line[start] == line[mid] &&
	  solvable(line, table, start+1, mid-start-1) &&
	  solvable(line, table, mid+1, len-(mid-start+2))) {
	return (table[start][len] = true);
      }
    }

  }

  return (table[start][len] = false);
}

void solve(const string &line)
{
  int table[MAX_LENGTH][MAX_LENGTH+1];
  
  for (unsigned int i = 0; i < line.length(); i++) {
    for (unsigned int j = 0; j <= line.length(); j++) {
      table[i][j] = -1;
    }
  }

  cout << (solvable(line, table, 0, line.length()) ? "solvable" : "unsolvable")
       << endl;
}

int main(void)
{
  string line;

  while (getline(cin, line)) {
    solve(line);
  }
  return 0;
}
