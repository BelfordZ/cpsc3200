#define PROBLEM 3 /* The problem # here */ 
#define TEAM 0 /* Your team # here */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdlib>

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

struct Person {
  string name;
  int IQ, height;
};

istream &operator>>(istream &is, Person &p)
{
  return (is >> p.name >> p.IQ >> p.height);
}

Person man[13], woman[13];
int graph[13][13];
int n;

int best[8192];

void search(int index, int subset)
{
  if (index >= n) {
    best[subset] = 0;
    return;
  } else if (best[subset] >= 0) {
    return;
  }
  for (int i = 0; i < n; i++) {
    if (((1 << i) & subset) == 0) {
      search(index+1, subset | (1 << i));
      int t = graph[index][i] + best[subset | (1 << i)];
      if (best[subset] < 0 || t < best[subset]) {
	best[subset] = t;
      }
    }
  }
}

void print(int index, int subset)
{
  if (index >= n) {
    return;
  }
  for (int i = 0; i < n; i++) {
    if (((1 << i) & subset) == 0) {
      int t = graph[index][i] + best[subset | (1 << i)];
      if (t == best[subset]) {
	out << woman[index].name << " " << man[i].name << " "
	     << graph[index][i] << endl;
	print(index+1, subset | (1 << i));
	return;
      }
    }
  }
}

void solve_problem(void)
{
  while (in >> n) {
    out << n << endl;
    for (int i = 0; i < n; i++) {
      in >> woman[i];
    }
    for (int i = 0; i < n; i++) {
      in >> man[i];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	graph[i][j] = abs(woman[i].IQ - man[j].IQ) +
	  abs(woman[i].height - man[j].height);
      }
    }
    for (int i = 0; i < 8192; i++) {
      best[i] = -1;
    }
    search(0, 0);
    print(0, 0);
    out << best[0] << endl;
  }
}
