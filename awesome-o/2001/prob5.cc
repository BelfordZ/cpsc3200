#define PROBLEM 5 /* The problem # here */ 
#define TEAM 0 /* Your team # here */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <algorithm>

/*
 * Big integer implementation
 *
 * Author: Howard Cheng
 *
 * Each digit in our representation represents LOG_BASE decimal digits
 *
 */

#include <cstring>
#include <cstdlib>
#include <climits>
#include <cctype>
#include <cassert>

using namespace std;

/* MAX_DIGIT should be defined to ensure that there is no overflow      */
/* it should be one digit more than the specified bound (for division), */
/* or a few more for safety.                                            */
#define MAX_DIGIT 100
#define BASE 10000
#define LOG_BASE 4
#define FMT_STR "%04d"

typedef int BigNum[MAX_DIGIT];

/*
 * For all operations taking a "result" parameter, it cannot be the
 * same as one of the operands unless stated otherwise.
 *
 */

/* a = b */
static void copy(BigNum a, const BigNum b);

/* a = 0 */
static void clear(BigNum a);

/* a == 0 */
static int is_zero(BigNum a);

/*
 * return   1 if a > b
 *          0 if a = b
 *         -1 if a < b	
 */
static int compare(const BigNum a, const BigNum b);

/* result = a + b,
 * result can be the same as one of the operands
 */
static void add(BigNum a, BigNum b, BigNum result);

/* result = a - b,
 * result can be the same as one of the operands
 * assumes a >= b
 */
static void subtract(BigNum a, BigNum b, BigNum result);

/* a <<= amount, or a = a*BASE^amount */
static void lshift(BigNum a, int amount);

/* result = a * b, where b is a single digit 
 * result can be the same as a.
 */
static void mult_digit(BigNum a, int b, BigNum result);

/* result = a * b */
static void mult(BigNum a, BigNum b, BigNum result);

/* read BigNum from stdin */
static void read_num(BigNum a, const string &s);

/* write BigNum to stdout */
static void write_num(ostream &os, BigNum a);

/* perform assignment a = b */
static void copy(BigNum a, const BigNum b)
{
  int i;
  for (i = 0; i < MAX_DIGIT; i++) {
    a[i] = b[i];
  }
}

/* perform assignment a = 0 */
static void clear(BigNum a)
{
  int i;
  for (i = 0; i < MAX_DIGIT; i++) {
    a[i] = 0;
  }
}

/* perform comparison a == 0 */
static int is_zero(BigNum a)
{
  int i;
  for (i = 0; i < MAX_DIGIT; i++) {
    if (a[i]) {
      return 0;
    }
  }
  return 1;
}

/* perform comparison between a and b.
   Returns -1 if a < b
            0 if a == b
           +1 if a > b */
static int compare(const BigNum a, const BigNum b)
{
  int i;
  for (i = MAX_DIGIT-1; i >= 0; i--) {
    if (a[i] < b[i]) {
      return -1;
    } else if (a[i] > b[i]) {
      return 1;
    }
  }
  return 0;
}

/* performs result = a + b */
static void add(BigNum a, BigNum b, BigNum result)
{
  int sum, carry, i;
  carry = 0;
  for (i = 0; i < MAX_DIGIT; i++) {
    sum = a[i] + b[i] + carry;
    result[i] = (sum < BASE) ? sum : sum - BASE;
    carry = (sum >= BASE);
  }
  assert(carry == 0);       /* assert no overflow */
}

/* perform result = a - b.  assumes a >= b */
static void subtract(BigNum a, BigNum b, BigNum result)
{
  int diff, borrow, i;
  borrow = 0;
  for (i = 0; i < MAX_DIGIT; i++) {
    diff = a[i] - b[i] - borrow;
    result[i] = (diff >= 0) ? diff : diff + BASE;
    borrow = (diff < 0);
  }
  assert(borrow == 0);
}

/* perform a *= BASE^amount */
static void lshift(BigNum a, int amount)
{
  int i;

  if (!amount) {
    return;
  }

  for (i = MAX_DIGIT-1; i >= amount; i--) {
    a[i] = a[i-amount];
  }
  for (i = 0; i < amount; i++) {
    a[i] = 0;
  }
}

/* result = a * b, where b is a single digit 
 * result can be the same as a.
 */
static void mult_digit(BigNum a, int b, BigNum result)
{
  int i, carry;
  int prod;

  assert(0 <= b && b < BASE);
  carry = 0;
  for (i = 0; i < MAX_DIGIT; i++) {
    prod = b * a[i];
    result[i] = (carry + prod) % BASE;
    carry = (carry + prod) / BASE;
  }
  assert(carry == 0);
}

/* result = a * b */
static void mult(BigNum a, BigNum b, BigNum result)
{
  int i;
  BigNum temp1;

  clear(result);

  for (i = 0; i < MAX_DIGIT; i++) {
    if (b[i] != 0) {
      copy(temp1, a);
      lshift(temp1, i);
      mult_digit(temp1, b[i], temp1);
      add(temp1, result, result);
    }
  }
}

/* read BigNum from stdin */
static void read_num(BigNum a, const string &buffer)
{
  int i, j, k, len, limit, mult;

  len = buffer.length();
  clear(a);

  if (len % LOG_BASE == 0) {
    limit = len / LOG_BASE;
  } else {
    limit = len / LOG_BASE + 1;
  }

  j = len-1;
  for (i = 0; i < limit; i++) {
    mult = 1;
    for (k = 0; k < LOG_BASE; k++) {
      if (j >= 0) {
        a[i] += (buffer[j] - '0') * mult;
      }
      j--;
      mult *= 10;
    }
  }
}

/* write BigNum to stdout */
static void write_num(ostream &os, BigNum a)
{
  int i, k, writing;

  if (is_zero(a)) {
    os << "0";
  } else {
    k = 0;
    writing = 0;
    for (i = MAX_DIGIT-1; i >= 0; i--) {
      assert(0 <= a[i] && a[i] < BASE);
      if (writing) {
	os << setfill('0') << setw(4) << a[i];
      } else if (a[i]) {
        os << a[i];
        writing = 1;
      }
    }
  }
}

struct SignedBigNum {
  int sign;
  BigNum x;
  
  SignedBigNum() {
    sign = 0;
    clear(x);
  }
  
  SignedBigNum(const SignedBigNum &a) {
    sign = a.sign;
    copy(x, a.x);
  }

  SignedBigNum &operator=(const SignedBigNum &a) {
    sign = a.sign;
    copy(x, a.x);
    return *this;
  }
};

bool operator<(const SignedBigNum &a, const SignedBigNum &b)
{
  if (a.sign != b.sign) {
    return a.sign < b.sign;
  } else if (a.sign >= 0) {
    return compare(a.x, b.x) == -1;
  } else {
    return compare(a.x, b.x) == 1;
  }
}

bool operator==(const SignedBigNum &a, const SignedBigNum &b)
{
  return (a.sign == b.sign && compare(a.x, b.x) == 0);
}

SignedBigNum operator-(SignedBigNum &a, SignedBigNum &b);

SignedBigNum operator+(SignedBigNum &a, SignedBigNum &b)
{
  SignedBigNum t;

  if (a.sign == 0) {
    t = b;
  } else if (b.sign == 0) {
    t = a;
  } else if (a.sign == b.sign) {
    t.sign = a.sign;
    add(a.x, b.x, t.x);
  } else if (a.sign < 0) {
    t = a;
    t.sign = 1;
    t = b - t;
  } else {
    t = b;
    t.sign = 1;
    t = a - t;
  }
  if (is_zero(t.x)) {
    t.sign = 0;
  }
  return t;
}

SignedBigNum operator-(SignedBigNum &a, SignedBigNum &b)
{
  SignedBigNum t;

  if (a.sign == 0) {
    t = b;
    t.sign = -1;
  } else if (b.sign == 0) {
    t = a;
  } else if (b.sign < 0) {
    t = b;
    t.sign = 1;
    t = a+t;
  } else if (a.sign < 0) {
    t = a;
    t.sign = 1;
    t = t + b;
    t.sign = -1;
  } else if (compare(a.x, b.x) >= 0) {
    t.sign = 1;
    subtract(a.x, b.x, t.x);
  } else {
    t.sign = -1;
    subtract(b.x, a.x, t.x);
  }
  if (is_zero(t.x)) {
    t.sign = 0;
  }
  return t;
}

SignedBigNum operator*(SignedBigNum &a, SignedBigNum &b)
{
  SignedBigNum t;
  if (a.sign == 0 || b.sign == 0) {
    return t;
  }
  t.sign = a.sign * b.sign;
  mult(a.x, b.x, t.x);
  return t;
}

istream &operator>>(istream &is, SignedBigNum &a)
{
  string s;
  is >> s;
  if (s[0] == '-') {
    a.sign = -1;
    s.erase(0,1);
  } else {
    a.sign = 1;
  }
  read_num(a.x, s);
  if (is_zero(a.x)) a.sign = 0;
  return is;
}

ostream &operator<<(ostream &os, SignedBigNum &a)
{
  if (a.sign < 0) {
    os << "-";
  }
  write_num(os, a.x);
  return os;
}


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

struct Term {
  SignedBigNum c, p;
  bool operator<(const Term &t) const
  {
    return t.p < p;
  }
};

istream &operator>>(istream &is, Term &t)
{
  return (is >> t.c >> t.p);
}

ostream &operator<<(ostream &os, Term &t)
{
  return (os << t.c << ' ' << t.p);
}

ostream &operator<<(ostream &os, vector<Term> &p)
{
  int count = 0;

  for (unsigned int i = 0; i < p.size(); i++) {
    if (p[i].c.sign) {
      count++;
    }
  }

  if (count == 0) {
    os << "1" << endl;
    os << "0 0" << endl;
    return os;
  }

  os << count << endl;
  for (unsigned int i = 0; i < p.size(); i++) {
    if (p[i].c.sign) {
      os << p[i].c << ' ' << p[i].p << endl;
    }
  }
  return os;
}

void add(vector<Term> &a, vector<Term> &b, vector<Term> &c)
{
  unsigned int i, j;
  Term t;

  c.clear();
  i = j = 0;
  while (i < a.size() && j < b.size()) {
    if (a[i].p == b[j].p) {
      t.p = a[i].p;
      t.c = a[i].c + b[j].c;
      c.push_back(t);
      i++; j++;
    } else if (b[j].p < a[i].p) {
      c.push_back(a[i++]);
    } else {
      c.push_back(b[j++]);
    }
  }
  while (i < a.size()) {
    c.push_back(a[i++]);
  }
  while (j < b.size()) {
    c.push_back(b[j++]);
  }
}

void mult(vector<Term> &a, vector<Term> &b, vector<Term> &c)
{
  unsigned int i, j;
  Term t;

  c.clear();

  for (i = 0; i < a.size(); i++) {
    vector<Term> d, e;
    for (j = 0; j < b.size(); j++) {
      t.c = a[i].c * b[j].c;
      t.p = a[i].p + b[j].p;
      d.push_back(t);
    }
    add(c, d, e);
    c = e;
  }
}

void compress(vector<Term> &p)
{
  vector<Term>::iterator i, j;

  i = p.begin();
  j = i+1;
  while (j < p.end()) {
    if (i->p == j->p) {
      j->c = j->c + i->c;
      i = p.erase(i);
      j = i+1;
    } else {
      i++;
      j++;
    }
  }
}

void solve_problem(void)
{
  string op;
  bool first = true;

  while (in >> op) {
    if (!first) {
      out << endl;
    }
    first = false;

    vector<Term> p1, p2;
    int d;
    Term t;
    in >> d;
    while (d-- > 0) {
      in >> t;
      p1.push_back(t);
    }
    in >> d;
    while (d-- > 0) {
      in >> t;
      p2.push_back(t);
    }
    sort(p1.begin(), p1.end());
    sort(p2.begin(), p2.end());
    compress(p1);
    compress(p2);
    
    vector<Term> result;

    if (op == "+") {
      add(p1, p2, result);
    } else {
      mult(p1, p2, result);
    }
    
    out << result;
  }
}
