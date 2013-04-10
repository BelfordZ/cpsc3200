#include <iostream>

using namespace std;
int slumpy(string slump) {
   if (slump.length() < 3) // must be at least 3 chars
      return 0;
   if (slump[0] != 'E' && slump [0] != 'D') // first char must be D or E
      return 0;
   if (slump [1] != 'F' ) // first char must be followed by an F
      return 0;

   // get pos of next char after the last consecutive F.
   int i = 2;
   for (i=2; slump[i] == 'F'; i++);

   //if the next and last char is a G, we have a slump
   if (i == slump.length()-1 && slump[i] == 'G') {
      return true;
   } else { // otherwise, we either dont have a slump, or we have a slump in the slump
      // so we recurse, checking from the next char after F, reading to the end
      return slumpy(slump.substr(i));
   }
}
int slimpy(string slimp) {
   if (slimp[0] != 'A' || slimp.length() < 2) // must be at least 2 chars, and start with A
      return 0;
   if (slimp[1] == 'H' && slimp.length() == 2)
      return 1;
   if (slimp[slimp.length()-1] != 'C')
      return 0;
   if (slimp[1] == 'B')
      return slimpy (slimp.substr(2, slimp.length() - 3));

   return slumpy(slimp.substr(1, slimp.length()-2));
}
int slurpy(string slurp) {
   for (int i=0; i<slurp.length(); i++) {
      if (slimpy(slurp.substr(0, i)) && slumpy(slurp.substr(i)))
	 return 1;
   }
   return 0;
}

int main() {
   int n;
   cin >> n;
   
   cout << "SLURPYS OUTPUT" << endl;
   string line;
   getline(cin, line);
   for (int i=0; i<n; i++) {
      getline(cin, line);
      cout << (slurpy(line) ? "YES" : "NO") << endl;
      
   }
   cout << "END OF OUTPUT" << endl;
   return 0;
}
