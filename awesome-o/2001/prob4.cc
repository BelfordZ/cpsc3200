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

int howmany[10] = { 0,0,3,3,3,3,3,4,3,4 };
char *letters[10] = { "", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS",
                      "TUV", "WXYZ" };

void solve_problem(void)
{
  string digits;

  while (in >> digits) {
    int curr = 0, i;
    for (curr = 0; curr < digits.length(); curr = i) {
      for (i = curr; i < digits.length() && digits[i] == digits[curr] &&
	     i - curr < howmany[digits[curr]-'0']; i++) ;
      out << letters[digits[curr]-'0'][i-curr-1];
      while (i < digits.length() && digits[i] == '#') {
	i++;
      }
    }
    out << endl;
  }
}
