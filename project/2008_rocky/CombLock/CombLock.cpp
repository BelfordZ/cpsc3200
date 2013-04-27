#include <iostream>

using namespace std;

int n;
int f(int x, int y, bool z) {
   if(z == true) {
      if(y >= x)
	 return y-x;
      else
	 return y+n-x;
   }
   else {
      if(y <= x)
	 return x-y;
      else
	 return x+n-y;
   }
}

int main() {
   int n=0, t1=0, t2=0, t3=0;
   while(cin >> n >> t1 >> t2 >> t3) {
      if (n==0 && t1==0 && t2==0 && t3 == 0){}
      else {
	 int max=-1, total=0;
	 for(int i=0; i<n; i++) {
	    total=0;
	    int tickStep = i;
	    // First move: two rotations, 
	    total += n*2; //two full clockwise revolutions
	    while (tickStep != t1){//if not landed on t1
	       total++;
	       tickStep = (tickStep - 1 + n) % n;
	    }
	    //2
	    total += n; //full ccw revolution
	    while (tickStep != t2){
	       total++;
	       tickStep = (tickStep + 1 + n) % n;
	    }
	    //3
	    while (tickStep != t3){
	       total++;
	       tickStep = (tickStep - 1 + n) % n;
	    }
	    if (total > max)
	       max = total;
	 }
	 cout << max << endl;
      }
   }
   return 0;
}
