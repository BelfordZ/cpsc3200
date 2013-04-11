#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
using namespace std;

void skipSpaces(istream& in) { while (isspace(in.peek())) in.ignore(); }
void readName(istream& in, string& n) {
   n = "";                                 // start with an empty name
   skipSpaces(in); in.ignore();            // skip to the " and ignore it
   while (in.peek()!= '"') n += in.get();  // append chars till " found
   in.ignore();                            // ignore closing " 
}
void printName(ostream& out, const string& n) { out << '"' << n << '"';}

struct source {
      string name;
      double amount;
};
istream& operator>>(istream& in, source& s){
   readName(in, s.name);
   skipSpaces(in); in.ignore(); // skip to comma and ignore it
   in >> s.amount;
   return in;
}
ostream& operator<<(ostream& out, const source& s) {
   printName(out, s.name);
   out << ',' << (long long)s.amount << endl;
   return out;
}

struct contract {
      string name;
      int priority;
      double volume;
};
istream& operator>>(istream& in, contract& c){
   readName(in,c.name);
   skipSpaces(in); in.ignore(); // skip to comma and ignore it
   in >> c.priority; 
   if (c.priority < 0) c.priority = 0;
   skipSpaces(in); in.ignore(); // skip to comma and ignore it
   in >> c.volume;
   return in;
}
ostream& operator<<(ostream& out, const contract& c) {
   printName(out,c.name);
   out << ',' << c.priority <<','<< (long long)c.volume << endl;
   return out;
}

int main()
{
   ifstream cin("prob1.dat");
   ofstream cout ("prob1.out");

   cout << "Program 1 by team RF" << endl;

   source s;
   while (cin >> s && s.name!="END") {
      // get the contracts to be filled 
      vector<contract> ordered;
      contract c;
      while (cin >> c && c.name != "END") ordered.push_back(c);

      // now fill the contracts
      int firstP = 0;
      double totalAvailable = s.amount;
      while (firstP < ordered.size()) {   // award each priority
	 double totalNeeded = 0.0;

	 // calculate amount of water requested by this priority
	 int nextP = firstP;
	 while (ordered[nextP].priority==ordered[firstP].priority &&
		nextP<ordered.size()) 
	    totalNeeded += ordered[nextP++].volume;

	 if (totalNeeded <= totalAvailable) // each gets what was ordered
	    totalAvailable -= totalNeeded;        
	 else {                             // prorate the awards
	    for (int j = firstP; j < nextP; j++) {
	       double prorate = ordered[j].volume/totalNeeded;
	       ordered[j].volume = totalAvailable * prorate;
	    }
	    totalAvailable = 0.0;        // used all the water
	 }
	 firstP = nextP;                 // do next priority
      }

      // print the water awards	  
      cout << s;
      for (int i = 0; i < ordered.size(); i++ )
	 cout << ordered[i];
      cout << c;  // print the END record for this source 
   }
   cout << s; // print the END record for the problem

   cout << "End of program 1 by team RF" << endl;

   return 0;
}
