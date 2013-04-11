#define PROBLEM 4 /* The problem # here */ 
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

void solve_problem(void)
{
  string code;

  while (in >> code) {
    int w = 10;
    int s = 0;
    for (unsigned int i = 0; i < code.length(); i++) {
      if (code[i] == '-') continue;
      int c = (code[i] == 'X') ? 10 : code[i] - '0';
      s += w * c;
      w--;
    }
    s %= 11;
    s = (11 - s) % 11;
    out << code << "-" << (char)((s == 10) ? 'X' : s + '0') << endl;
  }
}
