#define PROBLEM 0 /* The problem # here */ 
#define TEAM 0 /* Your team # here */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cctype>

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

void shake(char A[101][101], int n)
{
  bool up = true;
  char t;
  int i, j;

  for (j = 1; j <= n; j++) {
    if (up) {
      t = A[1][j];
      for (i = 1; i < n; i++) { 
	A[i][j] = A[i+1][j];
      }
      A[n][j] = t;
    } else {
      t = A[n][j];
      for (i = n; i > 1; i--) {
	A[i][j] = A[i-1][j];
      }
      A[1][j] = t;
    }
    up = !up;
  }
}

void rattle(char A[101][101], int n)
{
  bool right = true;
  char t;
  int i, j;

  for (i = 1; i <= n; i++) {
    if (!right) {
      t = A[i][1];
      for (j = 1; j < n; j++) { 
	A[i][j] = A[i][j+1];
      }
      A[i][n] = t;
    } else {
      t = A[i][n];
      for (j = n; j > 1; j--) {
	A[i][j] = A[i][j-1];
      }
      A[i][1] = t;
    }
    right = !right;
  }
}

void roll(char A[101][101], int n)
{
  bool right = true;
  char t, t2;
  int i, j;

  for (i = 1; i <= n/2; i++) {
    if (right) {
      t = A[i][n-i+1];
      for (j = n-i+1; j > i; j--) {
	A[i][j] = A[i][j-1];
      }
      t2 = A[n-i+1][n-i+1];
      for (j = n-i+1; j > i+1; j--) {
	A[j][n-i+1] = A[j-1][n-i+1];
      }
      A[i+1][n-i+1] = t;
      t = t2;
      t2 = A[n-i+1][i];
      for (j = i; j < n-i; j++) {
	A[n-i+1][j] = A[n-i+1][j+1];
      }
      A[n-i+1][n-i] = t;
      t = t2;
      for (j = i; j < n-i; j++) {
	A[j][i] = A[j+1][i];
      }
      A[n-i][i] = t;
    } else {
      t = A[i][i];
      for (j = i; j < n-i+1; j++) {
	A[i][j] = A[i][j+1];
      }
      t2 = A[n-i+1][i];
      for (j = n-i+1; j > i+1; j--) {
	A[j][i] = A[j-1][i];
      }
      A[i+1][i] = t;
      t = t2;
      t2 = A[n-i+1][n-i+1];
      for (j = n-i+1; j > i+1; j--) {
	A[n-i+1][j] = A[n-i+1][j-1];
      }
      A[n-i+1][i+1] = t;
      t = t2;
      for (j = i; j < n-i; j++) {
	A[j][n-i+1] = A[j+1][n-i+1];
      }
      A[n-i][n-i+1] = t;
    }
    right = !right;
  }
}

void solve_problem(void)
{
  string key, msg;

  while (in >> key) {
    in.ignore();
    getline(in, msg);

    int n;
    if ((n = (key[0]-'0')*10 + (key[1]-'0')) == 0) {
      n = 100;
    }

    char A[101][101];
    unsigned int k = 0, p = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
	if (p >= msg.length()) {
	  A[i][j] = k + 'A';
	  if (++k >= 26) {
	    k = 0;
	  }
	} else {
	  A[i][j] = toupper(msg[p++]);
	}
      }
    }

    for (unsigned int i = 2; i < key.length(); i++) {
      if (key[i] == 'S') {
	shake(A, n);
      } else if (key[i] == 'R') {
	rattle(A, n);
      } else if (key[i] == 'L') {
	roll(A, n);
      }
    }

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
	out << A[i][j];
      }
    }
    out << endl;
  }
}
