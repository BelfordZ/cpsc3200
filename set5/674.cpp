// my first attempt, too slow, tried to compute the number of ways each time a cent value was given.
// I searched around the web and realized a dynamic solution was required, and that the answers could
// all be precomputed.

#include <iostream>
#include <cmath>
using namespace std;

int main() {
  int perms[7490];
  perms[0] = 1; // obviously only 1 way to make 0 cents...

  int coins[5]; // 5 coin types
  coins[0] = 50;
  coins[1] = 25;
  coins[2] = 10;
  coins[3] = 5;
  coins[4] = 1;
  
  for (int i=0; i<5; i++) { // for each coin denomination
    for (int j=coins[i]; j<7490; j++) { // for each permutation sum between this coin and the end of array
      int tmp = j - coins[i]; //get index of them relative to the perm sum array
      perms[j] += perms[tmp]; // add all past computed perms
    }
  }
  
  int n=0;
  while (cin >> n) {
    cout << perms[n] << endl;
  }
  return 0;
}
