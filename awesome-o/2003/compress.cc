#define PROBLEM 0 /* The problem # here */ 
#define TEAM 0 /* Your team # here */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
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

int number(const string &s)
{
  int  sum = 0;
  for (unsigned int i = 0; i < s.length(); i++) {
    sum = sum*10 + (s[i] - '0');
  }
  return sum;
}

string decode(const string &F, const string &C)
{
  int numF = number(F);
  int numC = number(C);
  string R;

  if (numC > numF) {
    return C;
  }

  if (C.length() <= F.length()) {
    numF = number(F.substr(F.length()-C.length(), C.length()));
  }
  if (numF < numC) {
    if (C.length() <= F.length()) {
      return F.substr(0, F.length() - C.length()) + C;
    } else {
      assert(0);
      return "";
    }
  } else {
    if (C.length() <= F.length()) {
      R = F.substr(0, F.length() - C.length()) + C;
    } else {
      R = C;
    }
    int carry = 1;
    int i;
    for (i = R.length() - 1 - C.length(); i >= 0; i--) {
      if (R[i] == '9') {
	R[i] = '0';
	carry = 1;
      } else {
	R[i] = R[i] + 1;
	carry = 0;
	break;
      }
    }
    if (i < 0 && carry) {
      R.insert(0, "1");
    }
    return R;
  }
}

void solve_problem(void)
{
  string F, C, R;

  getline(in, F, '-');
  getline(in, R);
  while (!in.eof()) {
    for (unsigned int i = 1; i <= R.length(); i++) {
      C = R.substr(R.length()-i, i);
      if (decode(F, C) == R) {
	out << F << '-' << C << endl;
	break;
      }
    }
    getline(in, F, '-');
    getline(in, R);
  }
}
