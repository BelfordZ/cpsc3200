/*
 * Solution for Casino Advantage
 *
 * The basic idea is to use dynamic programming.  Let 
 *
 * P(n,m,k) = probability that k distinct numbers appear when rolling an
 *            m balls into n-slotted roulette.
 *
 * Then we have the following recurrence:
 *
 * P(n,0,0) = 1
 * P(n,m,0) = P(n,0,k) = 0                                  if m > 0 or k > 0
 * P(n,m,k) = P(n,m-1,k)*(k/n) + P(n,m-1,k-1)*(n-(k-1))/n   if m > 0 and k > 0
 *
 * The last recurrence above splits the problem into two cases:
 *   a) the first m-1 rolls already hit k distinct numbers, and the
 *      last roll is a repeat
 *   b) the first m-1 rolls only hit k-1 distinct numbers.  The last roll
 *      is distinct from the first m-1 rolls.
 *
 */

//
// Fraction implementation
//
// Author: Darcy Best
//
// Does NOT ever check for division by 0.
// Division by 0 will only cause a runtime error if you use the
//   toDouble() function.
//

#include <iostream>
#include <cstdlib>
using namespace std;

// Change this to whatever integer data type will prevent overflow
//   - BigInteger works with this class
typedef long long int dataType;

class Fraction{
public:
  Fraction(dataType num=0,dataType denom=1);
	
  double toDouble() const;
	
  void reduce();
	
  // Changes the fraction itself.
  void selfReciprocal();
	
  // Returns a new fraction, leaving the original.
  Fraction reciprocal() const;
	
  Fraction& operator+=(const Fraction& x);
  Fraction& operator-=(const Fraction& x);
  Fraction& operator*=(const Fraction& x);
  Fraction& operator/=(const Fraction& x);
	
  bool operator<(const Fraction& x) const;
  bool operator==(const Fraction& x) const;
	
  dataType num,denom;
};

Fraction operator+(const Fraction& x,const Fraction& y);
Fraction operator-(const Fraction& x,const Fraction& y);
Fraction operator*(const Fraction& x,const Fraction& y);
Fraction operator/(const Fraction& x,const Fraction& y);

istream& operator>>(istream& is,Fraction& x);
ostream& operator<<(ostream& os,const Fraction& x);

Fraction::Fraction(dataType n,dataType d){
  if(d < 0){
    num = -n;
    denom = -d;
  } else {
    num = n;
    denom = d;
  }
  reduce();
}

double Fraction::toDouble() const{
  return 1.0*num/denom;
}

// Howard's GCD function with no checks
dataType gcd(dataType a, dataType b)
{
  dataType r;
  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}

void Fraction::reduce(){
  dataType g = gcd(abs(num),denom);
  num /= g;
  denom /= g;
}

void Fraction::selfReciprocal(){
  swap(num,denom);
  if (denom < 0) {
    num = -num;
    denom = -denom;
  }
}

Fraction Fraction::reciprocal() const{
  return Fraction(denom,num);
}

// Overflow potential in the denominator.
// I've tried to factor out as much as possible before,
//   But be careful.
//
//   (w)/(a*g) + (z)/(b*g)
// = (w*b)/(a*g*b) + (a*z)/(a*g*b)
// = (w*b + a*z)/(a*g*b)
Fraction& Fraction::operator+=(const Fraction& x){
  dataType g = gcd(denom,x.denom);
	
  dataType a = denom / g;
  dataType b = x.denom / g;
	
  num = num * b + x.num * a;
  denom *= b;
	
  reduce();
	
  return (*this);
}

Fraction& Fraction::operator-=(const Fraction& x){
  dataType g = gcd(denom,x.denom);
  dataType a = denom / g;
  dataType b = x.denom / g;
	
  num = num * b - x.num * a;
  denom *= b;
	
  reduce();
  return (*this);
}

Fraction& Fraction::operator*=(const Fraction& x){
  num *= x.num;
  denom *= x.denom;
  reduce();
  return (*this);
}

Fraction& Fraction::operator/=(const Fraction& x){
  num *= x.denom;
  denom *= x.num;
	
  if(denom < 0){
    num = -num;
    denom = -denom;
  }
  reduce();
  return (*this);
}

// Careful with overflow. If it is an issue, you can compare the
// double values, but you SHOULD check for equality BEFORE converting
bool Fraction::operator<(const Fraction& x) const{
  return (num*x.denom) < (x.num*denom);
}

bool Fraction::operator==(const Fraction& x) const{
  return (num == x.num) && (denom == x.denom);
}

Fraction operator+(const Fraction& x,const Fraction& y){
  Fraction a(x);
  a += y;
  return a;
}

Fraction operator-(const Fraction& x,const Fraction& y){
  Fraction a(x);
  a -= y;
  return a;
}

Fraction operator*(const Fraction& x,const Fraction& y){
  Fraction a(x);
  a *= y;
  return a;
}

Fraction operator/(const Fraction& x,const Fraction& y){
  Fraction a(x);
  a /= y;
  return a;
}

// Note that you can read in Fractions of two forms:
// a/b (With any number of space between a,/,b) - The input "points" to
//      the NEXT character after the denom (White space or not)
// c   (Just an integer - The input "points" to the next NON-WHITE SPACE
//      character. Careful when mixing this with getline.)
istream& operator>>(istream& is,Fraction& x){
  is >> x.num;
	
  char ch;
  is >> ch;
  if(ch != '/'){
    is.putback(ch);
    x.denom = 1;
  } else {
    is >> x.denom;
    if(x.denom < 0){
      x.num = -x.num;
      x.denom = -x.denom;
    }
    x.reduce();
  }
	
  return is;
}

// Will output 5 for 5/1 and 0 for 0/1. If you want always
//    fractions, get rid of the if statement
ostream& operator<<(ostream& os,const Fraction& x){
  os << x.num;
  if(x.num != 0 && x.denom != 1)
    os << '/' << x.denom;
  return os;
}

Fraction P[11][11][11];

void init()
{
  for (int n = 1; n <= 10; n++) {
    P[n][0][0] = 1;
    for (int km = 1; km <= 10; km++) {
      P[n][km][0] = P[n][0][km] = 0;
    }
  }

  for (int n = 1; n <= 10; n++) {
    for (int m = 1; m <= 10; m++) {
      for (int k = 1; k <= 10; k++) {
	P[n][m][k] = P[n][m-1][k] * Fraction(k, n) +
	  P[n][m-1][k-1] * Fraction(n-(k-1), n);
      }
    }
  }
}

int main(){
  init();

  int T;
  cin >> T;
  while (T-- > 0) {
    int N, M, K;
    cin >> N >> M >> K;
    cout << P[N][M][K] << endl;
  }
  return 0;
}
