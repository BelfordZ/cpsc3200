#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

const double epsilon = 10E-4;

int main()
{
   vector<int> house;
   int n, pointI, homeI;
   cin >> n;
   cout.precision(1);
   while (n--)
   {
      cin >> pointI >> homeI;
      house.clear();

      for (int i = 0, d; i < homeI; ++i)
      {
	 cin >> d;
	 house.push_back(d);
      }
      sort(house.begin(), house.end());

      double a = 0;
      double b;
      double c = house[house.size() - 1];
      do
      {
	 b = (c + a) / 2.0;
	 int pointsRequired =  1;
	 double covered = house[0] + b;
	 for (size_t i = 0; i < house.size(); ++i)
	    if (house[i] > covered)
	       covered = house[i] + b, ++pointsRequired;
	 
	 if (pointsRequired > pointI)
	 a = b;
	 else
	    c = b;
      } while (c - a > epsilon);
      
      cout << fixed << (round(b * 10) / 20.0) << endl;
   }
   return 0;
}
