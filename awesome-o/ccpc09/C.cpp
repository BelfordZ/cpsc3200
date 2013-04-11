#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>

using namespace std;

int A, B, C, D, E, F;

void solve()
{
  //
  // let's say we charge Alex's laptop t1 minutes (in total) and
  //                     Sonny's laptop t2 minutes
  //
  // Then the change in charge at the end is:
  //
  // Alex:   B*t1 - C*t2
  // Sonny: -F*t1 + E*t2
  //
  // If we can solve the system of t1, t2 such that the RHS is positive
  // and t1,t2 is nonnegative, then we can do this indefinitely.  By
  // making the RHS arbitrarily small (but positive) we can ensure that
  // neither charge is 0 or above 100.
  //
  // Applying Cramer's rule, we see that if the determinant of the system is 
  // positive then there is a unique solution for t1, t2 >= 0.  If the
  // determinant is 0 then we can find a solution with RHS = [0,0] to remain
  // at the same charge indefinitely.
  //
  // If the determinant is negative, we want to see how long it will take to
  // get to RHS = [-A, -D].  We use Cramer's rule to solve this and see that
  // t1, t2 >= 0 only if determinant is negative.  Again, if we want we can
  // set the RHS to be epsilon * [-A, -D] to make sure that neither charge
  // goes out of range.  Then the solution would be epsilon * [t1, t2].
  // By choosing a sequence of epsilons whose sum approaches 1, we see that
  // we can keep the two laptops running for t1+t2 minutes.
  // 

  double det = B*E - C*F;
  if (det >= 0) {
    cout << "Sonny and Alex are safe" << endl;
  } else {
    double t1, t2;

    t1 = (-A*E - C*D)/det;
    t2 = (-B*D - A*F)/det;
    cout << (int)floor(t1+t2+0.5) << endl;
  }
}

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    cin >> A >> B >> C >> D >> E >> F;
    solve();
  }

  return 0;
}
