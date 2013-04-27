// Problem H: Post Office
// Solution by Zach Belford

// adhoc method. plain logic. These ones sure make you
// hate yourself when it doesn't work yet it is so simple.
#include <iostream>
#include <algorithm> 
using namespace std;

double dims[3];
void clear() {
   for (int i=0; i<1000; i++) {
      dims[3] = 0;
   }
}
// checks if global dims is a letter
bool isLetter() {
   bool one = false;
   if (( 125  <= dims[2] && dims[2] <= 290 ) &&
       ( 90   <= dims[1] && dims[1] <= 155 ) &&
       ( 0.25 <= dims[0] && dims[0] <= 7   )) {one=true;}
   return one;
}
bool isPacket() {
   bool one = false, two = false;
   if(125 <= dims[2] && 90 <= dims[1] && 0.25 <= dims[0] && // at least letter and
      (dims[2] > 290 || dims[1] > 155 || dims[0] > 7)) {one=true;} // one bigger than letter
	 
   if (dims[2] <= 380 && dims[1] <= 300 && dims[0] <= 50) {two=true;} //must be no more than...
   return one && two;
}
bool isParcel() {
   bool one = false, two = false;
   if (( (125  <= dims[2]) && (90 <= dims[1]) && (0.25 <= dims[0]) ) &&
       ( (dims[2] > 380) || (dims[1] > 300) || (dims[0] > 50) )) {one=true;}

   //length & girth calc
   if ( ( 2 * dims[0] ) + ( 2 * dims[1] ) + dims[2] <= 2100 ) {two=true;}
   return one && two;
}

int main() {
   while (cin>>dims[0]>>dims[1]>>dims[2]) {
      if (dims[0]==0) return 0;
      
      sort(dims, dims+3);
      
      if      (isLetter()) cout << "letter" << endl;
      else if (isPacket()) cout << "packet" << endl;
      else if (isParcel()) cout << "parcel" << endl;
      else cout << "not mailable" << endl;
      clear();
   }
}
