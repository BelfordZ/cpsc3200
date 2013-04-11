#define PROBLEM 1 /* The problem # here */ 
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

int m, n;
string board[100];
double vol[100][100];
bool border[100][100];
int src_r, src_c, sink_r, sink_c;
const double threshold = 0.999999;

void read_board(void)
{
  for (int i = 0; i < m; i++) {
    getline(in, board[i]);
    int t;
    if ((t = board[i].find("+")) >= 0 && t < n) {
      src_r = i;
      src_c = t;
    }
    if ((t = board[i].find("-")) >= 0 && t < n) {
      sink_r = i;
      sink_c = t;
    }
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      vol[i][j] = 0;
      border[i][j] = false;
    }
  }
}

bool is_full(int i, int j)
{
  return (vol[i][j] > threshold);
}

bool all_full(void)
{
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] == ' ' && !is_full(i,j)) {
	return false;
      }
    }
  }
  return true;
}

bool is_boundary(int i, int j)
{
  return ((board[i][j] == ' ' || board[i][j] == '-') && !is_full(i,j) && 
	  (is_full(i-1,j) || is_full(i+1,j) || is_full(i,j-1) || 
	   is_full(i,j+1)));
}

int count_boundary(void)
{
  int count = 0;
  for (int i = 1; i < m-1; i++) {
    for (int j = 1; j < n-1; j++) {
      if (border[i][j] = is_boundary(i, j)) {
	count++;
      }
    }
  }
  return count;
}

void solve_problem(void)
{
  while ((in >> m >> n) && (m || n)) {
    in.ignore();     // skip \n
    read_board();

    int t = 0;
    double overflow = 0;
    vol[src_r][src_c] = 1.0;
    while (!all_full()) {
      t++;
      
      int boundary = count_boundary();
      double fill = (1 + overflow) / boundary;
      overflow = 0;
      for (int i = 1; i < m; i++) {
	for (int j = 1; j < n; j++) {
	  if (!border[i][j]) continue;
	  vol[i][j] += fill;
	  if (is_full(i,j)) {
	    overflow += vol[i][j] - 1;
	    vol[i][j] = 1;
	  }
	}
      }
      vol[sink_r][sink_c] = 0;
    }
    out << t+1 << endl;
  }
}
