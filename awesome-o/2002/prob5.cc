#define PROBLEM 5 /* The problem # here */ 
#define TEAM 0 /* Your team # here */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <climits>

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

string code[10] = {
  "88", "DB", "A2", "92", "D1", "94", "84", "DA", "80", "D0"
};

string dotcode[10] = {
  "08", "5B", "22", "12", "51", "14", "04", "5A", "00", "50"
};

void round_up(string &value, unsigned int i)
{
  int carry = 1;
  
  if (value[--i] == '.') {
    i--;
  }
  do {
    int t = (value[i] - '0') + carry;
    carry = (t >= 10);
    t %= 10;
    value[i] = t + '0';
    i--;
    if (i >= 0 && value[i] == '.') {
      i--;
    }
  } while (i >= 0 && carry);
  if (carry) {
    value.insert(0, "1");
  }
}

void solve_problem(void)
{
  unsigned int width, prec;
  string value;
  unsigned int i;

  while (in >> width) {
    in.ignore(INT_MAX, ',');
    in >> prec;
    in.ignore(INT_MAX, ',');
    getline(in, value);

    while (value.length() > 1 && value[0] == '0') {
      value.erase(0, 1);
    }
    unsigned int p = value.find(".");
    if (p == 0) {
      p++;
      value.insert(0, "0");
    }
    if (p == string::npos) {
      p = value.length();
      value.append(".");
    }
    for (i = 0; i < prec+1; i++) {
      value.append("0");
    }
    if (prec > width - p) {
      prec = width - p;
    }

    unsigned int q = p + prec + 1;
    
    int prev_digit = ((value[q-1] == '.') ? value[q-2] : value[q-1]) - '0';
    if (value[q] > '5' || value[q] == '5' && prev_digit % 2 == 1) {
      round_up(value, q);
    }

    p = value.find(".");
    unsigned int len = p + prec;

    bool first = true;
    for (i = 0; i < width-len; i++) {
      if (!first) out << " ";
      out << "FF";
      first = false;
    }
    for (i = 0; i < p-1; i++) {
      if (!first) out << " ";
      out << code[value[i]-'0'];
      first = false;
    }
    if (!first) out << " ";
    out << dotcode[value[p-1]-'0'];
    for (i = 0; i < prec; i++) {
      out << " " << code[value[p+i+1]-'0'];
    }
    out << endl;
  }
}
