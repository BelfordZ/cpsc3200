
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

int main () {

   ifstream cin ( "prob2.dat" );
   ofstream cout ( "prob2.out" );

   cout << "Program 2 by team RF" << endl;
      
   string dice;
   while (cin >> dice) {	 
      char usdn[4];       // create the rotation around the east-west axis
      usdn[0] = dice[4];  // up
      usdn[1] = dice[3];  // south
      usdn[2] = dice[5];  // down
      usdn[3] = dice[2];  // north
      
      if (usdn[0] == '1' || usdn[2] == '1')  // if 1 is on up or down
	 while (usdn[3] != '1')              // rotate it onto the other axis
	    rotate(usdn,usdn+1,usdn+4);      // I picked north
	 
      char eswn[4];          // create the rotation around the up-down axis
      eswn[0] = dice[0];     // east
      eswn[1] = usdn[1];     // south; use the south from the updated usdn
      eswn[2] = dice[1];     // west
      eswn[3] = usdn[3];     // north; use the north from the updated usdn
      while (eswn[0] != '1') // and rotate until 1 is on the east
	 rotate(eswn,eswn+1,eswn+4); 

      usdn[1] = eswn[1];      // update usdn from equivalent positions on eswn
      usdn[3] = eswn[3];
      while ( usdn[3] != '2' )// and rotate until 2 is on the north
	 rotate (usdn,usdn+1,usdn+4); 

      if ( usdn[0] == '3' )    // if 3 is up then right handed else left handed
	 cout << "right" << endl;
       else
	 cout << "left" << endl;
   }

   cout << "End of program 2 by team RF" << endl;
   return 0;
}
