#define PROBLEM 6 /* The problem # here */ 
#define TEAM 0 /* Your team # here */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

using namespace std;

ifstream in;
ofstream out; 
void solve_problem(); 

int main(void)
{
  char filename[64];
  sprintf(filename, "prob%d.dat", PROBLEM); 
  in.open(filename, ios::in); 
  if (!in) { 
    cout << "could not open input file " << filename << endl; 
    exit(1); 
  } 
  sprintf(filename, "prob%d.out", PROBLEM); 
  out.open(filename, ios::out); 
  if (!out) { 
    cout << "could not open output file " << filename << endl; 
    exit(1);
  } 
  out << "Program " << PROBLEM << " by team " << TEAM << endl; 
  solve_problem(); 
  out << "End of program " << PROBLEM << " by team " << TEAM << endl;
  return 0; 
}

bool board[100][100];
int mcount[100][100];
char output[100][100];
int m, n;
int dr[8] = {-1,-1,-1,0,0,1,1,1};
int dc[8] = {-1,0,1,-1,1,-1,0,1};

void clear_board(void)
{
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      board[i][j] = false;
      mcount[i][j] = 0;
      output[i][j] = '#';
    }
  }
}

void compute_count(void)
{
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < 8; k++) {
	int r = i+dr[k], c = j+dc[k];
	if (0 <= r && r < m && 0 <= c && c < n && board[r][c]) {
	  mcount[i][j]++;
	}
      }
    }
  }
}

void print_output(void)
{
  out << "+";
  for (int i = 0; i < n; i++) {
    out << "-";
  }
  out << "+" << endl;
    
  for (int i = 0; i < m; i++) {
    out << "|";
    for (int j = 0; j < n; j++) {
      out << output[i][j];
    }
    out << "|" << endl;
  }

  out << "+";
  for (int i = 0; i < n; i++) {
    out << "-";
  }
  out << "+" << endl;
}

void process_lost(int r, int c)
{
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (output[i][j] == '#' && board[i][j]) {
	output[i][j] = (i == r && j == c) ? '!' : '*';
      }
    }
  }
}

void process_good(int r, int c)
{
  output[r][c] = (mcount[r][c]) ? mcount[r][c] + '0' : ' ';
  if (mcount[r][c] == 0) {
    for (int i = 0; i < 8; i++) {
      int r2 = r + dr[i];
      int c2 = c + dc[i];
      if (0 <= r2 && r2 < m && 0 <= c2 && c2 < n && output[r2][c2] == '#') {
	process_good(r2, c2);
      }
    }
  }
}

void solve_problem(void)
{
  bool first = true;
  while (in >> m >> n) {
    clear_board();
    
    int mines, r, c;
    in >> mines;
    while (mines-- > 0) {
      in >> r >> c;
      board[r-1][c-1] = true;
    }
    compute_count();

    string line;
    bool lost = false;
    getline(in, line);     // skip \n
    while (getline(in, line) && line.length() > 0) {
      if (lost) continue;
      sscanf(line.c_str(), "%d %d", &r, &c);
      if (board[r-1][c-1]) {
	process_lost(r-1, c-1);
	lost = true;
      } else {
	process_good(r-1, c-1);
      }
      if (!first) {
	out << endl;
      }
      print_output();
      first = false;
    }
    
  }
}
