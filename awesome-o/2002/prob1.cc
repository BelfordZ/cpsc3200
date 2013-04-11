#define PROBLEM 1 /* The problem # here */ 
#define TEAM 0 /* Your team # here */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <climits>
#include <vector>
#include <cmath>

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

struct Contract {
  string name;
  int priority;
  long long volume;
};

istream &operator>>(istream &is, Contract &c)
{
  is.ignore(INT_MAX, '"');
  getline(is, c.name, '"');
  is.ignore(INT_MAX, ',');
  is >> c.priority;
  is.ignore(INT_MAX, ',');
  is >> c.volume;
  return is;
}

void get_src(string &name, long long &volume)
{
  in.ignore(INT_MAX, '"');
  getline(in, name, '"');
  in.ignore(INT_MAX, ',');
  in >> volume;
}

void solve_problem(void)
{
  string src_name;
  long long src_vol;

  get_src(src_name, src_vol);
  while (src_name != "END") {
    out << '"' << src_name << '"' << ',' << src_vol << endl;
    vector<Contract> contracts;
    Contract c;
    in >> c;
    while (c.name != "END") {
      contracts.push_back(c);
      in >> c;
    }

    unsigned int curr = 0, i = 0;
    while (curr < contracts.size()) {
      long long total = 0;
      while (contracts[i].priority == contracts[curr].priority) {
	total += contracts[i].volume;
	i++;
      }
      for (unsigned int j = curr; j < i; j++) {
	out << '"' << contracts[j].name << '"' << ','
	    << contracts[j].priority << ',';
	if (src_vol >= total) {
	  out << contracts[j].volume << endl;
	} else {
	  long long t = static_cast<long long>(
            floor(static_cast<double>(contracts[j].volume)*src_vol/total));
	  out << t << endl;
	}
      }
      src_vol -= total;
      if (src_vol < 0) {
	src_vol = 0;
      }
      curr = i;
    }

    out << "\"END\",0,0" << endl;
    get_src(src_name, src_vol);
  }
  out << "\"END\",0" << endl;
}
