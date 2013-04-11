#define PROBLEM 3 /* The problem # here */ 
#define TEAM 0 /* Your team # here */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cctype>
#include <cassert>

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

string result(string expr)
{
  if (expr[0] == '!') {
    return "!" + result(expr.substr(1, expr.length()-1));
  } else if (islower(expr[0])) {
    return expr.substr(0, 1);
  } else {
    // look for & or |
    int count = 0;
    for (unsigned int i = 0; i < expr.length(); i++) {
      if (expr[i] == '(') count++;
      if (expr[i] == ')') count--;
      if (expr[i] == '&' && count == 1) {
	return "(" + result(expr.substr(1,i-1)) + "&" +
	  result(expr.substr(i+1,expr.length()-1-(i+1))) + ")";
      } else if (expr[i] == '|' && count == 1) {
	return "!(!" + result(expr.substr(1,i-1)) + "&!" +
	  result(expr.substr(i+1,expr.length()-1-(i+1))) + ")";
      }
    }
  }
  assert(0);
  return "";
}

void solve_problem(void)
{
  string expr;

  while (in >> expr) {
    out << result(expr) << endl;
  }
}
