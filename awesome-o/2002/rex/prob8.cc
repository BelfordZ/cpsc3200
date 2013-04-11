#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

bool valid(char c) { return isalnum(c) || c == '-' || c == '_'; }

void skipToValid(istream& in) {
   while (in.peek() != EOF && !valid(in.peek())) in.ignore();
}

void readValid(istream& in, string& str) {
   str.erase();
   while (true) {
      char c = in.peek();
      if (c == EOF) break;
      if (c == '.' && str[str.length()-1] == '.') break;  // two periods
      if (!valid(c)&& c != '.') break;
      str += in.get();
   }
   int last = str.length()-1;
   if (str[last] == '.') str.erase(last);  // get rid of trailing .
}


int main()
{
   ifstream cin("prob8.dat");
   ofstream cout ("prob8.out");

   cout << "Program 8 by team RF" << endl;

   for (;;) {
      string user = "";
      for (;;) {
	 skipToValid(cin);
	 readValid(cin,user);
	 char c = cin.get();
	 if (cin.eof() || c == '@') break;
      }
      
      // have eof or valid username followed by an '@' symbol
      if (cin.eof()) break;

      for (;;) {
	 string server = "";
	 readValid(cin,server);
	 if (server.empty()) break; // no valid server found
	 cout << user << '@' << server << endl; // print the address
	 if (cin.peek() != '@') break; // no possible nested address
	 user = server; 	 // an @ is coming so possible nested address
	 cin.ignore();           // skip the @ sign
      }
   }

   cout << "End of program 8 by team RF" << endl;

   return 0;
}
