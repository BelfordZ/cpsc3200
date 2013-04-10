#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
   string line1;
   string line2;
   int testCase = 1;
   while (getline(cin, line1) && getline(cin, line2)) {
      int l1l = line1.length();
      int l2l = line2.length();

      // make and init 2d vector for our lcs matrix (make a border around it with 0's as well)
      vector<vector<int> > lcs;
      lcs.resize(l1l+1);
      for (int i = 0; i < l1l+1; i++) {
	 lcs[i].resize(l2l+1);
	 for (int j = 0; j < l2l+1; j++) {
	    lcs[i][j] = 0;
	 }
      }
      
      //bubble check!
      for (int i = l1l-1; i >= 0; i--) {
	 for (int j = l2l-1; j >= 0; j--) {
	    //carry curr lcs
	    lcs[i][j] = lcs[i+1][j+1];

	    //if we have a char match
	    if (line1[i] == line2[j])
	       lcs[i][j]++;

	    int currMax = max(lcs[i+1][j], lcs[i][j+1]);
	    lcs[i][j] = max(currMax, lcs[i][j]);
	 }
      }
      cout << "Case #" << testCase << ": you can visit at most " << lcs[0][0] << " cities." << endl;
      testCase++;
   }
}
