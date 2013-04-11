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
  /*
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
  */
  cout << "Program " << PROBLEM << " by team " << TEAM << endl;

  solve_problem();
  cout << "End of program " << PROBLEM << " by team " << TEAM << endl;

  return 0; 
}

void solve_problem(void)
{
  string state, button;

  cin >> state;
  while (cin >> button) {
    for (unsigned int i = 0; i < state.length(); i++) {
      state[i] = ((state[i] - '0') + (button[i] - '0')) % 10 + '0';
    }
  }
  cout << state << endl;
}
