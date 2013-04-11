#define PROBLEM 0 /* The problem # here */ 
#define TEAM 0 /* Your team # here */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <vector>

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

const int GRIDSIZE = 10, PLANKS = 20;

string grid[GRIDSIZE];
int plank[PLANKS];
int num_planks;

struct Leg {
  int plank, r, c;
  Leg(int p, int rr, int cc)
    : plank(p), r(rr), c(cc) { }
};

bool in_range(int r, int c)
{
  return 0 <= r && r < GRIDSIZE && 0 <= c && c < GRIDSIZE;
}

bool find_path(int sr, int sc, int dr, int dc, bool used[], vector<Leg> &path)
{
  int delta_r[4] = { -1, 1, 0, 0 };
  int delta_c[4] = { 0, 0, -1, 1 };

  if (sr == dr && sc == dc) {
    return true;
  }
  for (int i = 0; i < num_planks; i++) {
    if (used[i]) continue;

    for (int j = 0; j < 4; j++) {
      int r = sr + delta_r[j]*plank[i];
      int c = sc + delta_c[j]*plank[i];

      if (in_range(r, c) && grid[r][c] == '*') {
	used[i] = true;
	path.push_back(Leg(i+1,r+1,c+1));
	if (find_path(r, c, dr, dc, used, path)) {
	  return true;
	}
	used[i] = false;
	path.pop_back();
      }
    }
  }
  return false;
}

void solve_problem(void)
{
  for (int i = 0; i < GRIDSIZE; i++) {
    getline(in, grid[i]);
  }
  while (in >> num_planks) {
    for (int i = 0; i < num_planks; i++) {
      in >> plank[i];
    }
    
    vector<Leg> path;
    bool used[PLANKS];

    fill(used, used+num_planks, false);
    if (grid[0][0] == '*' && 
	find_path(0, 0, GRIDSIZE-1, GRIDSIZE-1, used, path)) {
      for (unsigned int i = 0; i < path.size(); i++) {
	out << "place plank " << path[i].plank << " to stump ("
	    << path[i].r << "," << path[i].c << ")" << endl;
      }
    } else {
      out << "no solution possible" << endl;
    }
    out << endl;
  }
  
}
