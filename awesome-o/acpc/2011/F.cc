//
// go through all the cells and mark them as potential ones (depending
// on whether they are adjacent to vertical or horizontal roads).  Then
// trace them.
//

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int L, W, N;
string grid[100];

int trace(int r, int c, int dr, int dc)
{
  int count = 0;
  while (grid[r][c] == 'H' || grid[r][c] == 'V') {
    count++;
    r += dr;
    c += dc;
  }
  return count;
}

void solve()
{
  int dr[4] = { -1, 0, 0, 1 };
  int dc[4] = {  0, -1, 1, 0 };

  cin >> L >> W >> N;

  for (int i = 0; i < L; i++) {
    cin >> grid[i];
  }

  for (int r = 1; r < L-1; r++) {
    for (int c = 1; c < W-1; c++) {
      if (grid[r][c] != '.') continue;
      int horiz = 0, vert = 0;
      for (int d = 0; d < 4; d++) {
	int rr = r + dr[d], cc = c + dc[d];
	if (grid[rr][cc] == '-') {
	  horiz++;
	} else if (grid[rr][cc] == '|') {
	  vert++;
	} else if (grid[rr][cc] == '+') {
	  horiz = vert = 100;
	}
      }
      
      if (horiz + vert != 1) continue;
      if (horiz) {
	grid[r][c] = 'H';
      } else {
	grid[r][c] = 'V';
      }
    }
  }

  int maxcars = 0;
  for (int r = 1; r < L-1; r++) {
    for (int c = 1; c < W-1; c++) {
      int len = 0;
      if (grid[r][c] == 'H' && grid[r][c-1] != 'H') {
	len = trace(r, c, 0, 1);
      } else if (grid[r][c] == 'V' && grid[r-1][c] != 'V') {
	len = trace(r, c, 1, 0);
      }
      maxcars += (len+1)/3;
    }
  }

  if (N <= maxcars) {
    cout << "LOCATION OKAY" << endl;
  } else {
    cout << "CHOOSE ANOTHER LOCATION" << endl;
  }
}

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    solve();
  }
  return 0;
}
