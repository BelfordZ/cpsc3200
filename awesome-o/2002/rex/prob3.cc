#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
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

int diffs[15][15];
bool used[15];
int currMatch[15];
int bestMatch[15];
int bestDev;
int howMany;

void findBestDev(int currFemale, int currDev) {

   if (currFemale == howMany) { // we have a match 
      if (currDev < bestDev) {  // if better than the previous one, save it
	 bestDev = currDev;
	 for (int i =0; i < howMany; i++) bestMatch[i] = currMatch[i];
      }
      return;
   }

   // check to see if there are minimums in the levels below that
   // will be less than the best deviation so far
   int tempDev = currDev;
   for (int cf = currFemale; cf < howMany; cf++) {
      int min = diffs[cf][0];
      for (int cm=1; cm<howMany; cm++)
	 if (!used[cm] && diffs[cf][cm] < min) min = diffs[cf][cm];
      tempDev += min;
      if (tempDev >= bestDev) return;
   }

   // if we get here, we are ready to find the best match for the next
   // female
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
      person female[15];
      person male[15];
      for (int i = 0; i < howMany; i++) cin >> female[i];
      for (int i = 0; i < howMany; i++) cin >> male[i];
      for (int i=0; i < howMany; i++) 
	 for (int j=0; j< howMany; j++)
	    diffs[i][j] = abs(female[i].iq - male[j].iq) +
 	                  abs(female[i].height - male[j].height);
      cerr << endl;
      cerr << "   | ";
      for (int i =0; i < howMany; i++) cerr << setw(3) << i;
      cerr << endl;
      for (int i=0; i< howMany; i++) {
	 cerr << setw(2) << i << " | ";
	 for (int j =0; j < howMany; j++)
	    cerr << setw(3) << diffs[i][j];
	 cerr << endl;
      }
      for(int i =0;i < howMany; i++) used[i] = false;
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
