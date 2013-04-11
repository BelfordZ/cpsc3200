#define PROBLEM 8 /* The problem # here */ 
#define TEAM 0 /* Your team # here */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
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

void process(const string &line, unsigned int p)
{
  unsigned int start, end;
  bool prev_dot;
  
  if (p > 0 && line[p-1] == '.' || p < line.length() - 1 && line[p+1] == '.') {
    return;
  }

  // look for user
  prev_dot = false;
  for (start = p-1; start >= 0 && 
	 (isalnum(line[start]) || line[start] == '-' || line[start] == '_' ||
	  (line[start] == '.' && !prev_dot)); start--) {
    prev_dot = (line[start] == '.');
  }
  if (prev_dot) {
    start++;
  }
  start++;
  if (p - start <= 0) {
    return;
  }
  
  // look for server
  prev_dot = false;
  for (end = p+1; end < line.length() &&
	 (isalnum(line[end]) || line[end] == '-' || line[end] == '_' ||
	  (line[end] == '.' && !prev_dot)); end++) {
    prev_dot = (line[end] == '.');
  }
  if (prev_dot) {
    end--;
  }
  if (end - 1 - p <= 0) {
    return;
  }
  out << line.substr(start, end-start) << endl;

}

void solve_problem(void)
{
  string line;

  while (getline(in, line)) {
    int p;
    for (int i = 0; (p = line.find("@", i)) != string::npos; i = p+1) {
      process(line, p);
    }
  }
}
