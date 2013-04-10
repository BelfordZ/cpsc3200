// I started with one approach as seen at the bottom.
// found out that I misread the problem, and fixed my solution.
#include <iostream>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

int main() {
  int n;
  while (cin >> n) {
    if (n==0)
      return 0;
    vector<int> cumSum;
    for (int i=0; i<n; i++) {
      int tmp;
      cin >> tmp;
      cumSum.push_back(tmp);
    }
    // instead of former solution, this time we just put the value of the current
    // cumulative sum, if its greater than the non-sum.
    for (int i=0; i<n; i++) {
      if (cumSum[i-1] + cumSum[i] > cumSum[i]) {
	cumSum[i] = cumSum[i-1] + cumSum[i];
      }
    }
    int maxWin = 0;
    for (int i=0; i<n; i++) {
      maxWin = max(maxWin, cumSum[i]);
    }
    if (maxWin > 0) {
      cout << "The maximum winning streak is " << maxWin << "." << endl;
    } else {
      cout << "Losing streak." << endl;
    }
  }
  return 0;
}
    /*
    int tmpMaxSum = 0;
    int currMaxSum = 0;
    for (int i=0; i<n; i++) {
      int temp;
      cin >> temp;
      if (temp >= 0) {
	tmpMaxSum+=temp;

	if (tmpMaxSum > currMaxSum)
	  currMaxSum = tmpMaxSum;

      } else {
	tmpMaxSum = 0;
      }
    }
    if (currMaxSum > 0)
      cout << "The maximum winning streak is " << currMaxSum << "." << endl;
    else
      cout << "Losing streak." << endl;
  }
}
    */
