#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

bool comparison(pair<double,int> left, pair<double,int> right)
{
   if (left.first == right.first)
      return (left.second > right.second);
   return (left.first < right.first);
    
}
int main()
{
   int numOfCases;
   cin >> numOfCases;

   for (int i=0; i<numOfCases; i++)
   {
      if (i != 0)
	 cout << endl << endl;
      int numJobs;
      cin >> numJobs;
      
      vector<pair<double,int> > weights;
      
      for (int j=0; j<numJobs; j++)
      {
	 int Tj, Sj;
	 cin >> Tj >> Sj;

	 if (Tj == 0)
	    weights.push_back(make_pair(0, j));
	 else
	    weights.push_back(make_pair((double)((double)Sj/(double)Tj), j));


	 //today....
      }
      sort(weights.begin(), weights.end(), comparison);
      for (int k=weights.size()-1; k>=0; k--)
      {
	 if (k != weights.size()-1)
	    cout << " ";
	 //cout << weights[k].first;
	 cout << weights[k].second+1;
      }
   }
   cout << endl;
   return 0;
}
