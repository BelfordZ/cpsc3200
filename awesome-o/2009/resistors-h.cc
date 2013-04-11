#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <cassert>
#include <climits>
#include <cstdlib>

using namespace std;

// only deals with nonnegative rationals
class Rational {
private:
  long long n, d;
  
  void reduce()
  {
    // be a bit conservative here
    if (n > INT_MAX/10 || d > INT_MAX/10) {
      cout << "Overflow detected" << endl;
      exit(1);
    }

    long long a, b, r;

    a = n;
    b = d;
    while (b != 0) {
      r = a % b;
      a = b;
      b = r;
    }
    n /= a;
    d /= a;
  }
  
public:
  Rational(long long numer = 0, long long denom = 1)
    : n(numer), d(denom)
  {
    reduce();
  }

  Rational &operator+=(const Rational &r)
  {
    long long nn = n*r.d + r.n*d;
    long long dd = d*r.d;
    
    n = nn;
    d = dd;
    reduce();
    return *this;
  }

  Rational inverse() const
  {
    return Rational(d,n);
  }
  
  friend istream &operator>>(istream &is, Rational &r);
  friend ostream &operator<<(ostream &is, const Rational &r);
};

istream &operator>>(istream &is, Rational &r)
{
  long long n, d;

  if (!(is >> n)) {
    return is;
  }
  char c;
  is >> c;

  assert(c == '/');
  is >> d;
  r.n = n;
  r.d = d;
  r.reduce();
  return is;
}

ostream &operator<<(ostream &os, const Rational &r)
{
  return os << r.n << '/' << r.d;
}

Rational solve(string line)
{
  while (line.length() > 0 && isspace(line[0])) {
    line.erase(0, 1);
  }
  while (line.length() > 0 && isspace(line[line.length()-1])) {
    line.erase(line.length()-1, 1);
  }

  if (line[0] != '(') {
    istringstream iss(line);
    Rational r;
    iss >> r;
    return r;
  }

  int level = 0;
  int last = 1;
  Rational ans(0,1);
  bool serial = false;
  bool parallel = false;
  for (unsigned int i = 1; i < line.length()-1; i++) {
    if (line[i] == '(') {
      level++;
    } else if (line[i] == ')') {
      level--;
    } else if (line[i] == '&' && !level) {
      // it can only be & 
      assert(!parallel);
      ans += solve(line.substr(last, i-last));
      serial = true;
      last = i+1;
    } else if (line[i] == '|' && !level) {
      assert(!serial);
      ans += solve(line.substr(last, i-last)).inverse();
      parallel = true;
      last = i+1;
    }
  }
  if (serial) {
    ans += solve(line.substr(last, line.length()-1-last));
  } else {
    ans += solve(line.substr(last, line.length()-1-last)).inverse();
  }

  return parallel ? ans.inverse() : ans;
}

int main(void)
{
  string line;

  while (getline(cin, line)) {
    cout << solve(line) << endl;
  }
  return 0;
}
