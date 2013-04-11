#include <fstream>
#include <iomanip>

using namespace std;

double prob(int N)
{
  /* idea: The probability that the first knot is good is
   *
   *  1 - N/2 / C(N, 2) = (N-2)/(N-1)
   *
   * if the first knot is successful, then it is reduced to the case
   * with N-2 strands.
   *
   * So the probability is:
   *
   * (N-2)(N-4) ... 2 
   * ----------------
   * (N-1)(N-3) ... 3
   *
   */
  
  double p = 1;
  int i;

  for (i = 2; i <= N-2; i+=2) {
    p *= i;
  }
  for (i = 3; i <= N-1; i+=2) {
    p /= i;
  }
  return p;
}

int main(void)
{
  int N;

  ifstream in("knots.in");
  ofstream out("knots.out");

  while (in >> N) {
    out << fixed << setprecision(5) << prob(N) << endl;
  }
  return 0;
}
