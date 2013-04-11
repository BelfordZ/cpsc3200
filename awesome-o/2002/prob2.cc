#define PROBLEM 2 /* The problem # here */ 
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

int nbrs[24][3] = 
{
  {0,2,5}, {0,4,2}, {0,3,4}, {0,5,3},
  {1,3,5}, {1,4,3}, {1,2,4}, {1,5,2},
  {2,1,5}, {2,4,1}, {2,0,4}, {2,5,0},
  {3,0,5}, {3,4,0}, {3,1,4}, {3,5,1},
  {4,2,0}, {4,1,2}, {4,3,1}, {4,0,3},
  {5,0,2}, {5,2,1}, {5,1,3}, {5,3,0}
};

void solve_problem(void)
{
  string dice;

  while (in >> dice) {
    bool left = false;
    for (int i = 0; i < 24; i++) {
      if (dice[nbrs[i][0]] == '1' && dice[nbrs[i][1]] == '2' &&
	  dice[nbrs[i][2]] == '3') {
	left = true;
      }
    }
    out << ((left) ? "left" : "right") << endl;
  }
}
