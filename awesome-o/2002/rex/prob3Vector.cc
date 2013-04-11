#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include <cstdlib>
using namespace std;

class person
{
   public :
      string name;
      int iq;
      int height;
};

istream& operator>>(istream& in, person& p){
   in >> p.name >> p.iq >> p.height;
   return in;
}

vector<vector<int> > diffs;
vector<bool> used;
vector<int> currMatch;
vector<int> bestMatch;
int bestDev;
int howMany;

void findBestDev(int currFemale, int currDev) {

   if (currFemale == howMany) {
      if (currDev <= bestDev) {
	 bestDev = currDev;
	 bestMatch = currMatch;
      }
      return;
   }

   int tempDev = currDev;
   for (int i = currFemale; i < howMany; i++) {
      int min = diffs[i][0];
      for (int j=1; j<howMany; j++)
	 if (!used[j] && diffs[i][j] < min) min = diffs[i][j];
      tempDev += min;
      if (tempDev >= bestDev) return;
   }

   for (int currMale = 0; currMale < howMany; currMale++)
      if (!used[currMale]) {
	 used[currMale] = true;
	 currMatch[currFemale] = currMale;
	 findBestDev(currFemale+1, currDev + diffs[currFemale][currMale]);
	 used[currMale] = false;
      }
}

int main()
{
   ifstream cin("prob3.dat");
   ofstream cout ("prob3.out");

   cout << "Program 3 by team RF" << endl;

   while (cin >> howMany) {
      vector<person> female(howMany);
      vector<person> male(howMany);
      for (int i = 0; i < howMany; i++) cin >> female[i];
      for (int i = 0; i < howMany; i++) cin >> male[i];
      diffs.resize(howMany);
      for (int i=0; i < howMany; i++) {
	 diffs[i].resize(howMany);
	 for (int j=0; j< howMany; j++)
	    diffs[i][j] = abs(female[i].iq - male[j].iq) +
 	                  abs(female[i].height - male[j].height);
      }
      used.resize(howMany,false);
      currMatch.resize(howMany);
      bestMatch.resize(howMany);
      bestDev = 1000000;
      findBestDev(0,0);
      cout << howMany << endl;
      for (int i = 0; i < howMany; i++) 
	 cout << female[i].name << ' ' << male[bestMatch[i]].name
	      << ' ' << diffs[i][bestMatch[i]] << endl;
      cout << bestDev << endl;
   }

   cout << "End of program 3 by team RF" << endl;

   return 0;
}
