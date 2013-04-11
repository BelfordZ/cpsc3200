#define PROBLEM 7 /* The problem # here */ 
#define TEAM 0 /* Your team # here */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <climits>
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

char graph[26][26];

void clear_graph(void)
{
  int i, j;
  for (i = 0; i < 26; i++) {
    for (j = 0; j < 26; j++) {
      graph[i][j] = 0;
    }
  }
}

int parse_graph(const string &line, unsigned int start, int root)
{
  int node = line[start] - 'A';
  if (root != -1) {
    graph[root][node] = graph[node][root] = 1;
  }
  if (start+1 >= line.length() || line[start+1] != '(') {
    return 1;
  }
  int i = start+2;
  while (line[i] != ')') {
    i += parse_graph(line, i, node);
  }
  return (i+1) - start;
}

bool print_path(int src, int dest, bool visited[])
{
  visited[dest] = true;
  if (src == dest) {
    out << (char)(src + 'A');
    return true;
  }
  for (int i = 0; i < 26; i++) {
    if (graph[i][dest] && !visited[i] && print_path(src, i, visited)) {
      out << "->" << (char)(dest + 'A');
      return true;
    }
  }
  return false;
}

void solve_problem(void)
{
  string line;
  char src, dest;
  bool visited[26];

  getline(in, line);
  while (!in.eof()) {
    clear_graph();
    parse_graph(line, 0, -1);
    out << line << endl;
    while (getline(in, line)) {
      if (line.length() == 0) {
	out << endl;
	break;
      }
      sscanf(line.c_str(), "%c %c", &src, &dest);
      for (int i = 0; i < 26; i++) {
	visited[i] = false;
      }
      print_path(src-'A', dest-'A', visited);
      out << endl;
    }

    getline(in, line);
  }
    
  
}
