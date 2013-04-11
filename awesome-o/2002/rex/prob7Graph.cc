
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

void print(ostream& out,  stack<char> path) {
   while(!path.empty()) {
      out << path.top();
      path.pop();
      if (!path.empty()) out << "->";
   }
   out << endl;
}

stack<char> route(const vector<vector<bool> >& net, char source, char dest) {
   char curr;
   queue<char> stations;
   stations.push(source);
   vector<char> firstSeen(26,'\0');
   while (!stations.empty()) {
      curr = stations.front();
      stations.pop();
      if (curr == dest) break;
      for(int i = 0; i < 26; i++) {   
	 if (net[curr-'A'][i] && firstSeen[i] == '\0') { // connected & unseen
	    stations.push(i+'A');  // add to the queue
	    firstSeen[i] = curr;   // mark as seen
	 }
      }
   }
   stack<char> path;   // starting with the dest, create the path
   while (curr != source) {
      path.push(curr);
      curr = firstSeen[curr-'A'];
   }
   path.push(curr);   // add the source to the path
   return path;
}


int main () {
   vector<vector<bool> > network(26);
   stack<char> parents;
   
   ifstream cin ( "prob7.dat" );
   ofstream cout ( "prob7.out" );

   cout << "Program 7 by team RF" << endl;
      
   char prev;
   char input;
   for (int i = 0; i < 26; i++) network[i].resize(26);

   bool first = true;
   while (cin >> prev)  {
      for (int i =0; i<26; i++)
	 for (int j=0; j<26; j++) network[i][j] = false;
      
      if (!first) cout << endl;
      first = false; 
      cout << prev;
      while (true) {
	 cin.get(input); cout << input;
	 if (input == '\n') break;
	 if (input == '(') parents.push(prev);
	 else if (input == ')') parents.pop();
  	 else {
	    network[input -'A'] [parents.top()-'A'] = true;
	    network[parents.top()-'A'] [input -'A'] = true;
	    prev = input;
	 }
      }
      char source, dest;
      while (cin.peek() != '\n') {
	 cin >> source >> dest;
	 cin.ignore(1,'\n');
	 if (cin.eof()) break;
	 print(cout, route(network, source, dest));
      }
   }
   
   cout << "End of program 7 by team RF" << endl;
   return 0;
}
