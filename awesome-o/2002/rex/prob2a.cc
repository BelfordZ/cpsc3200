
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
   ifstream cin("prob2.dat");
   ofstream cout ("prob2.out");
   
   cout << "Program 2 by team RF" << endl;
   string dice;
   
   while(cin>>dice) {
      if (dice == "162534" ||
	  dice == "163452" ||
	  dice == "164325" ||
	  dice == "165243" ||
	  dice == "251643" ||
	  dice == "253416" ||
	  dice == "254361" ||
	  dice == "256134" ||
	  dice == "341625" ||
	  dice == "342561" ||
	  dice == "345216" ||
	  dice == "346152" ||
	  dice == "431652" ||
	  dice == "432516" ||
	  dice == "435261" ||
	  dice == "436125" ||
	  dice == "521634" ||
	  dice == "523461" ||
	  dice == "524316" ||
	  dice == "526143" ||
	  dice == "612543" ||
	  dice == "613425" ||
	  dice == "614352" ||
	  dice == "615234" )
	 cout << "right" << endl;
      else
	 cout << "left" << endl;
   }
   
   cout << "End of program 2 by team RF" << endl;
   return 0;
}
