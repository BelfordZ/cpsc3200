// I used a piece of code from the internet instead of howards code.
// somehow I couldnt get this one to work.

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;
 
/* Finds longest strictly increasing subsequence. O(n log k) algorithm. */
void find_lis(vector<int> &a, vector<int> &b)
{
  vector<int> p(a.size());
  int u, v;
 
  if (a.empty()) return;
 
  b.push_back(0);
 
  for (size_t i = 1; i < a.size(); i++) 
    {
      // If next element a[i] is greater than last element of current longest subsequence a[b.back()], just push it at back of "b" and continue
      if (a[b.back()] < a[i]) 
	{
	  p[i] = b.back();
	  b.push_back(i);
	  continue;
	}
 
      // Binary search to find the smallest element referenced by b which is just bigger than a[i]
      // Note : Binary search is performed on b (and not a). Size of b is always <=k and hence contributes O(log k) to complexity.    
      for (u = 0, v = b.size()-1; u < v;) 
	{
	  int c = (u + v) / 2;
	  if (a[b[c]] < a[i]) u=c+1; else v=c;
	}
 
      // Update b if new value is smaller then previously referenced value 
      if (a[i] < a[b[u]]) 
	{
	  if (u > 0) p[i] = b[u-1];
	  b[u] = i;
	}
    }
 
  for (u = b.size(), v = b.back(); u--; v = p[v]) b[u] = v;
}

int main()
{
  // get numOfTestCases
  string tmp;
  int numOfTests;
  getline(cin, tmp);
  istringstream ss(tmp);
  ss >> numOfTests;

  // clear empty line
  getline(cin, tmp);

  //for each test case
  for (int i=0; i<numOfTests; i++) {
    vector<int> missles;
    string missle;
    while (getline(cin, missle, '\n')) {
      istringstream ss1(missle);
      int tmp;
      ss1 >> tmp;
      missles.push_back(tmp);
    }
    vector<int> subseqList;
    find_lis(missles, subseqList);

    cout << "Max hits: " << subseqList.size() << endl;
    for (int j=0; j<subseqList.size(); j++) {
      cout << missles[subseqList[j]] << endl;
    }
  }
  return 0;
}
