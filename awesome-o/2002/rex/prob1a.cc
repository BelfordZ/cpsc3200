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

class source
{
      friend istream& operator>>(istream& in, source& s){
	 readName(in, s.n);
	 skipSpaces(in); in.ignore(); // skip to comma and ignore it
	 in >> s.amt;
	 return in;
      }
      friend ostream& operator<<(ostream& out, const source& s) {
	 printName(out, s.n);
	 out << ',' << (long long)s.amt << endl;
	 return out;
      }
   public :
      source () { amt = 0.0; }
      double amount() const { return amt; }
      string name() const {return n; }
   private:
      string n;
      double amt;
};

class contract
{
      friend istream& operator>>(istream& in, contract& c){
	 readName(in,c.n);
	 skipSpaces(in); in.ignore(); // skip to comma and ignore it
	 in >> c.p; 
	 if (c.p < 0) c.p = 0;
	 skipSpaces(in); in.ignore(); // skip to comma and ignore it
	 in >> c.vol;
	 return in;
      }
      friend ostream& operator<<(ostream& out, const contract& c) {
	 printName(out,c.n);
	 out << ',' << c.p <<','<< (long long)c.vol << endl;
	 return out;
      }
   public :
      contract () { p = 1001; vol = 0.0; }
      string name() const { return n; }
      int priority() const {return p;}
      double volume() const {return vol; }
      void setVol(double amt) { vol = amt; }
   private :
      string n;
      int p;
      double vol;
};

int main()
{
   ifstream cin("prob1.dat");
   ofstream cout ("prob1.out");

   cout << "Program 1 by team RF" << endl;

   source s;
   while (cin >> s && s.name()!="END") {

      // get the contracts to be filled 
      vector<contract> ordered;
      contract c;
      while (cin >> c && c.name() != "END") ordered.push_back(c);

      // now fill the contracts
      int firstP = 0;
      double totalAvailable = s.amount();
      while (firstP < ordered.size()) {   // award each priority
	 int p = ordered[firstP].priority();
	 double totalNeeded = 0.0;

	 // calculate amount of water requested by this priority
	 int nextP = firstP;
	 while (ordered[nextP].priority() == p && nextP < ordered.size()) {
	    totalNeeded += ordered[nextP].volume(); nextP++;
	 }

	 if (totalNeeded <= totalAvailable) // each gets what was ordered
	    totalAvailable -= totalNeeded;        
	 else {                             // prorate the awards
	    for (int j=firstP; j<nextP; j++) {
	       double prorate = ordered[j].volume()/totalNeeded;
	       ordered[j].setVol(totalAvailable * prorate);
	    }
	    totalAvailable = 0.0;        //used all the water
	 }
	 firstP = nextP;                 // do next priority
      }

      // print the water awards	  
      cout << s;
      for (int i =0; i < ordered.size(); i++ ) cout << ordered[i];
      cout << c;  // print the END record for this source 
   }

   cout << s; // print the END record for the problem

   cout << "End of program 1 by team RF" << endl;

   return 0;
}
