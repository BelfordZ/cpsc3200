#define PROBLEM 6 /* The problem # here */ 
#define TEAM 0 /* Your team # here */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <set>
#include <map>
#include <utility>
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


string rotate(string p)
{
  string best;

  best = p;
  for (int i = 0; i < 2; i++) {
    char t = p[0];
    p[0] = p[1];
    p[1] = p[2];
    p[2] = t;
    if (p < best) {
      best = p;
    }
  }
  return best;
}

typedef pair<int,int> Coord;

Coord get_coord(const string &s)
{
  int row, col;
  char NS, EW;
  if (sscanf(s.c_str(), "%c%d%c%d", &NS, &row, &EW, &col) == 2) {
    col = 0;
  }
  if (NS == 'S') {
    row = -row + 1;
  }
  if (EW == 'W') {
    col = -col;
  }
  return pair<int,int>(row,col);
}

bool up(const Coord &coord)
{
  int row = coord.first;
  int col = coord.second;
  
  return (abs(row % 2) != abs(col % 2));
}

bool adjacent(map<Coord,string> &board, const Coord &coord)
{
  bool found = false;
  Coord nbr = coord;
  if (up(coord)) {
    nbr.second -= 1;
    found |= (board.find(nbr) != board.end());
    nbr.second += 2;
    found |= (board.find(nbr) != board.end());
    nbr.first--; nbr.second--;
    found |= (board.find(nbr) != board.end());
  } else {
    nbr.second -= 1;
    found |= (board.find(nbr) != board.end());
    nbr.second += 2;
    found |= (board.find(nbr) != board.end());
    nbr.first++; nbr.second--;
    found |= (board.find(nbr) != board.end());
  }
  return found;
}

bool adj_match(map<Coord,string> &board, const Coord &coord)
{
  bool match = true;
  string p1 = board[coord], p2;
  Coord nbr = coord;
  if (up(coord)) {
    nbr.second -= 1;
    if (board.find(nbr) != board.end()) {
      p2 = board[nbr];
      match = match && (p1[0] == p2[2] && p1[2] == p2[0]);
    }
    nbr.second += 2;
    if (board.find(nbr) != board.end()) {
      p2 = board[nbr];
      match = match && (p1[0] == p2[1] && p1[1] == p2[0]);
    }
    nbr.first--; nbr.second--;
    if (board.find(nbr) != board.end()) {
      p2 = board[nbr];
      match = match && (p1[1] == p2[2] && p1[2] == p2[1]);
    }
  } else {
    nbr.second -= 1;
    if (board.find(nbr) != board.end()) {
      p2 = board[nbr];
      match = match && (p1[0] == p2[1] && p1[1] == p2[0]);
    }
    nbr.second += 2;
    if (board.find(nbr) != board.end()) {
      p2 = board[nbr];
      match = match && (p1[0] == p2[2] && p1[2] == p2[0]);
    }
    nbr.first++; nbr.second--;
    if (board.find(nbr) != board.end()) {
      p2 = board[nbr];
      match = match && (p1[1] == p2[2] && p1[2] == p2[1]);
    }
  }
  return match;
}

void solve_problem(void)
{
  string line;
  bool done = !getline(in, line);
  while (!done) {
    bool valid = true;
    bool first = true;
    set<string> pieces;
    map<Coord,string> board;

    while (!done && line.length() > 0) {
      unsigned int p = line.find(" ");
      Coord coord = get_coord(line.substr(0,p));
      cout << line << endl;
      string piece = line.substr(p+1, line.length()-(p+1));

      // check that the first move is N1
      if (first && coord != Coord(1,0)) {
	valid = false;
      }

      // check that the piece has not been used twice
      if (pieces.find(rotate(piece)) != pieces.end()) {
	valid = false;
      } else {
	pieces.insert(rotate(piece));
      }

      // check that the space has not been used before
      if (board.find(coord) != board.end()) {
	valid = false;
      } else {
	board[coord] = piece;
      }

      // if not the first one, check that it's adjacent to something
      if (!first && !adjacent(board, coord)) {
	valid = false;
      }

      // check for whether the vertices on adjacent pieces match
      if (!adj_match(board, coord)) {
	valid = false;
      }

      first = false;
      done = !getline(in, line);
    }
    out << ((valid) ? "valid" : "invalid") << endl;
    done = !getline(in, line);
  }
}
