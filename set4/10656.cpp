#include <iostream>
#include <vector>

using namespace std;

//checks if the set was all zeros
bool allZero(vector<int> v);

int main()
{
   int n;
   //for each input set
   while (cin >> n && n > 0)
   {
      vector<int> subset;
      //push it to a vect
      for (int i=0; i<n; i++)
      {
	 int temp;
	 cin >> temp;
	 subset.push_back(temp);
      }
      //if its non zero, print each element, removing the zeros
      if (!allZero(subset))
      {
	 bool printed = false;
	 for (int i=0; i<subset.size(); i++)
	 {    
	    if (subset[i] != 0)
	    {
	       if (printed) cout << " ";
	       cout << subset[i];
	       printed = true;
	    }
	 }
      }
      else // otherwise just print the zero...done
      {
	 cout << 0;
      }
      cout << endl;
   }
   
}

bool allZero(vector<int> v)
{
   for (int j=0; j<v.size(); j++)
   {
      if (v[j] > 0)
      {
	 return false;
      }
   }
   return true;
}
