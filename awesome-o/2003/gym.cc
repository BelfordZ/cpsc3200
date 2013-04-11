#define PROBLEM 0 /* The problem # here */ 
#define TEAM 0 /* Your team # here */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <sstream>
#include <iomanip>

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

int trans[10][10];
double total[10];
double prob[10][10];
int n;

void solve_problem(void)
{
  string s;

  getline(in, s);
  stringstream ss(s, stringstream::in);
  n = 0;
  while (ss >> trans[0][n]) {
    n++;
  }

  for (int i = 1; i < n; i++) {
    for (int j = 0; j < n; j++) {
      in >> trans[i][j];
    }
  }

  for (int i = 0; i < n; i++) {
    total[i] = 0;
    for (int j = 0; j < n; j++) {
      total[i] += trans[i][j];
    }
  }

  prob[0][0] = 1;
  for (int j = 1; j < n; j++) {
    prob[0][j] = 0;
  }

  for (int i = 1; i < 10; i++) {
    for (int j = 0; j < n; j++) {
      prob[i][j] = 0;
      for (int k = 0; k < n; k++) {
	prob[i][j] += prob[i-1][k] * trans[k][j] / total[k];
      }
    }
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < n; j++) {
      out << (j ? " " : "") << setprecision(5) << fixed << prob[i][j];
    }
    out << endl;
  }

}
