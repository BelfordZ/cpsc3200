//Problem 4883: Ropes
// Solution By Zach Belford

// adhoc solution. We find max pitches and the peak height in
// order to apply therules in adhoc fashion.
#include <iostream>
using namespace std;

int ropeLength[3] = {50, 60, 70};

int main() {
   int numPitches = 0;
   while(cin >> numPitches && numPitches != 0) {
      int pit[100];//max of 100 pitches
      int maxPitchGap=0;//must find this
      int peakHeight=0;//sum of all pitch gaps
      //cin, get max, sumation of pitch heights
      for (int ches=0; ches<numPitches; ches++){
	 cin>>pit[ches];
	 if (pit[ches]>maxPitchGap) {
	    maxPitchGap=pit[ches];
	 }					
	 peakHeight+=pit[ches];
      }
      //for each of the rope len's
      int ans[3];
      for (int i=0; i<3; i++) {
	 // get number of climbers that can be on this rope len
	 //with the current max pitch gap
	 int numClimbers = ropeLength[i] / maxPitchGap;
	 //enforce enough rope and enough climbers
	 if (ropeLength[i]<peakHeight*2 || numClimbers<1) { 
	    ans[i] = 0;
	 }
	 else 
	    ans[i] = numClimbers+1; // all good, we can have another!
      }
      cout << ans[0] << " " << ans[1] << " " << ans[2] << endl;
   }
   return 0;
}
