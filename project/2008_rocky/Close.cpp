#include <iostream>
#include <algorithm>
using namespace std;
double fixerUpper = 0.000000001;
int compare(double x, double y = 0) {
   if (x <= y + fixerUpper)
      if (x + fixerUpper < y)
	 return -1;
      else
	 return 0;
   else
      return 1;
}

int main() {
   double cals[3], fats[3], carbs[3], prots[3];
   while(cin>>cals[0]>>fats[0]>>carbs[0]>>prots[0]) {
      if (cals[0]==0 && fats[0]==0 && carbs[0]==0 && prots[0]==0){return 0;}
      else{
	 //lower bounded
	 carbs[1] = max(0.00, carbs[0]-0.5);
	 fats [1] = max(0.00, fats [0]-0.5);
	 prots[1] = max(0.00, prots[0]-0.5);
	 cals [1] = max(0.00, cals [0]-0.5);
	 //upper bounded
	 carbs[2] = carbs[0]+0.5;
	 fats [2] = fats [0]+0.5;
	 prots[2] = prots[0]+0.5;
	 cals [2] = cals [0]+0.5;
	 cout << carbs[1] << "--" << carbs[2] << endl;
	 double ans[2][3][2];
	 //lowerRoundedCarbs
	 ans[0][0][0] = carbs[1]*4;
	 ans[0][0][1] = carbs[2]*4;
	 //lowerRoundedFats
	 ans[0][1][0] = fats[1]*9;
	 ans[0][1][1] = fats[2]*9;
	 //lowerRoundedProts
	 ans[0][3][0] = prots[1]*4;
	 ans[0][3][1] = prots[2]*4;

	 //lowerRoundedCarbs
	 ans[1][0][0] = carbs[1]*4;
	 ans[1][0][1] = carbs[2]*4;
	 //lowerRoundedFats
	 ans[1][1][0] = fats[1]*9;
	 ans[1][1][1] = fats[2]*9;
	 //lowerRoundedProts
	 ans[1][3][0] = prots[1]*4;
	 ans[1][3][1] = prots[2]*4;

	 double sum[2];
	 sum[0] = ans[0][0][0] + ans[0][1][0] + ans[0][2][0];
	 sum[1] = ans[1][0][1] + ans[1][1][1] + ans[1][2][1];

	 if (compare(sum[0], cals[0]) < 1 && compare(cals[0], sum[1]) < 0)
	    cout << "yes" << endl;
	 else if ( compare(sum[0], cals[1]) < 0 && compare(cals[2], sum[1]) < 1)
	    cout << "yes" << endl;
	 else
	    cout << "no" << endl;
      }
   }
}
