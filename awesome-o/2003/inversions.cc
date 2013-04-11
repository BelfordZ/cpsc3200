#define PROBLEM 0 /* The problem # here */ 
#define TEAM 0 /* Your team # here */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <iomanip>

using namespace std;

ifstream in;
ofstream out; 
void solve_problem(); 

const int MAX_N = 20;
const int MAX_K = MAX_N*(MAX_N-1)/2;

long long F[MAX_N+1][MAX_K+1];

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

void solve_problem(void)
{
  int n, k, i;

  for (n = 1; n <= MAX_N; n++) {
    F[n][0] = 1;
    for (k = 1; k <= MAX_K; k++) {
      if (k > n*(n-1)/2) {
        /* no way: too many inversions */
	F[n][k] = 0;
      } else {
        /* we consider all the permutations of the right kind that starts
           with 1, 2, 3, ... etc. and recurse.  Fixing 1 as the first
           element does not reduce the number of inversions.  Fixing
           2 reduce inversions by 1.  Fixing 3 reduce inversions by 2,
           etc.  So we try fixing each one of them as the first element
           and stop as soon as we introduce too many inversions */
	F[n][k] = 0;
	for (i = k; i >= k - n + 1 && i >= 0; i--) {
	  F[n][k] += F[n-1][i];
	}
      }
    }
  }

  in >> n >> k;
  while (n || k) {
    if (k > n*(n-1)/2) {
      out << "0" << endl;
    } else {
      out << F[n][k] << endl;
    }
    in >> n >> k;
  }
}
