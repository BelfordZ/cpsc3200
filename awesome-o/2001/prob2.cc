#define PROBLEM 2 /* The problem # here */ 
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
  int a1, a2, a3, a4;
  int network, host;

  while (in >> a1) {
    in.ignore(); in >> a2; in.ignore(); in >> a3; in.ignore(); in >> a4;
    if ((a1 & (1 << 7)) == 0) {
      // class A
      network = a1;
      host = (a2 << 16) + (a3 << 8) + a4;
    } else if ((a1 & (1 << 6)) == 0) {
      // class B
      network = ((a1 & ~(1 << 7)) << 8) + a2;
      host = (a3 << 8) + a4;
    } else if ((a1 & (1 << 5)) == 0) {
      // class C
      a1 &= ~(1 << 7);
      a1 &= ~(1 << 6);
      network = (a1 << 16) + (a2 << 8) + a3;
      host = a4;
    }
    out << "prefix =" << setw(9) << network << "  suffix ="
	<< setw(9) << host << endl;
  }
}
