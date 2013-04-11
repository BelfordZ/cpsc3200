
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void rotate(string& side,int a, int b, int c, int d) {
   char temp = side[a];
   side[a] = side[b];
   side[b] = side[c];
   side[c] = side[d];
   side[d] = temp;
}

const int E = 0;
const int W = 1;
const int N = 2;
const int S = 3;
const int U = 4;
const int D = 5;

int main () {

   ifstream cin ( "prob2.dat" );
   ofstream cout ( "prob2.out" );

   cout << "Program 2 by team RF" << endl;
      
   string dice;
   while ( cin >> dice)  {	 
      // move the 1 to the east position
      if (dice[E] == '1' || dice[W] == '1' || dice[N] == '1' || dice[S] == '1') 
	 // the 1 is on one of these four sides so
	 // hold up and down fixed and rotate the other 4
	 while (dice[E] != '1') rotate(dice,N,E,S,W);
      else // the one is either up or down so
	   // hold north and south fixed and rotate the other 4
	 while (dice[E] != '1') rotate(dice,U,E,D,W); 
      
      // now get the 2 to the north position; keeping east and west fixed
      // note that 1 and 6 are on the east and west so 2 is on one of the others
      while (dice[N] != '2')  rotate(dice,U,N,D,S); // rotate the other 4

      if ( dice[U] == '3' )         // if up is a 3 then right else left
	 cout << "right" << endl;
       else
	 cout << "left" << endl;
   }
   
   cout << "End of program 2 by team RF" << endl;
   return 0;
}


