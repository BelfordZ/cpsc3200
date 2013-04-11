
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string path(const string& network, char child) {
   int index = 0;
   string temp = "";
   while (network[index] != child) {
      if (network[index]=='(') temp += network[index-1];
      else if (network[index]== ')') temp.erase(temp.length()-1);
      index++;
   }
   temp += child;
   return temp;
}


int main () {
   
   ifstream cin ( "prob7.dat" );
   ofstream cout ( "prob7.out" );

   cout << "Program 7 by team RF" << endl;
      
   string network;
   getline(cin,network);
   while (!cin.eof())  {
      cout << network << endl;
      while (cin.peek() != '\n') {
	 char source, dest;
	 cin >> source >> dest; cin.ignore(1,'\n');
	 if (cin.eof()) break;
	 string sourcePath = path(network, source);
	 string destPath = path(network, dest);

	 bool found = false;
	 int sourceLast = sourcePath.length()-1;
	 int destLast = destPath.length()-1;
	 int sourceMatch, destMatch;
	 for (int i=sourceLast; i>=0 && !found; i--)
	    for (int j=destLast; j>=0 && !found; j--)
	       if (destPath[j] == sourcePath[i]) {
		  sourceMatch = i;
		  destMatch = j;
		  found = true;
	       }
	 cout << sourcePath[sourceLast];
	 for (int i=sourceLast-1; i>=sourceMatch; i--)
	    cout << "->" << sourcePath[i];
	 for (int i=destMatch+1; i<= destLast; i++) cout << "->" << destPath[i];
	 cout << endl;
      }
      cin.ignore(1,'\n');  // skip the blank line
      getline(cin, network);
      if (cin.good()) cout << endl;  // print a blank line at end of data set
   }
   
   cout << "End of program 7 by team RF" << endl;
   return 0;
}
