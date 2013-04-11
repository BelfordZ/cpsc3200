#define PROBLEM 0 /* The problem # here */ 
#define TEAM 0 /* Your team # here */ 

#include <iostream>
#include <iomanip>
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

int cell_index(const string &s, int i)
{
  int r = (s[i+1]-'0')*10 + s[i+2]-'0';
  int c = (s[i+4]-'0')*10 + s[i+5]-'0';
  return (r-1)*20 + (c-1);
}

void print_cell(int i)
{
  int r = (i / 20) + 1;
  int c = (i % 20) + 1;
  out << "R" << setfill('0') << setw(2) << r;
  out << "C" << setfill('0') << setw(2) << c;
}

void solve_problem(void)
{
  const unsigned int max_cell = 400;
  bool graph[max_cell][max_cell];
  int order[max_cell];
  bool circular[max_cell];
  unsigned int count = 0;
  unsigned int i, j, k;

  for (i = 0; i < max_cell; i++) {
    order[i] = -1;
    circular[i] = false;
    for (j = 0; j < max_cell; j++) {
      graph[i][j] = false;
    }
    graph[i][i] = true;
  }
  
  string defn;
  while (in >> defn) {
    i = 0;
    int lhs = cell_index(defn, i);
    i += 7;
    if (order[lhs] < 0) {
      order[lhs] = count++;
    }
    while (i < defn.length() && (j = defn.find("R", i)) != string::npos) {
      int rhs = cell_index(defn, j);
      if (order[rhs] < 0) {
	order[rhs] = count++;
      }
      graph[order[lhs]][order[rhs]] = true;
      i = j + 6;
    }
  }
  
  for (k = 0; k < count; k++) {
    for (i = 0; i < count; i++) {
      for (j = 0; j < count; j++) {
	graph[i][j] |= (graph[i][k] && graph[k][j]);
      }
    }
  }
  
  for (i = 0; i < max_cell; i++) {
    if (order[i] < 0) continue;
    k = order[i];
    for (j = 0; j < count; j++) {
      if (j != k && graph[k][j] && graph[j][k]) {
	circular[k] = true;
	break;
      }
    }
  }



  for (i = 0; i < max_cell; i++) {
    if (order[i] < 0) continue;
    k = order[i];
    if (!circular[k]) {
      for (j = 0; j < count; j++) {
        if (j != k && circular[j] && graph[k][j]) {
          circular[k] = true;
        }
      }
    }
  }

  for (i = 0; i < max_cell; i++) {
    if (order[i] < 0) continue;
    k = order[i];
    print_cell(i);
    if (circular[k]) {
      out << " circular" << endl;
    } else {
      out << " ok" << endl;
    }
  }

}
