
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string isbn(const string& inISBN) {

   int sumProd = 0;
   for (int i=0, j=10; i < inISBN.length(); i++) 
      if (inISBN[i] != '-') sumProd += (inISBN[i]-'0') * j--;

   int checkDigit = ((sumProd/11 + 1) * 11 - sumProd) % 11; 

   if(checkDigit == 10)
      return inISBN + "-X";
   else
      return inISBN + "-" + (char)(checkDigit + '0');
}
	 

int main()
{
   ifstream cin("prob4.dat");
   ofstream cout ("prob4.out");

   cout << "Program 4 by team RF" << endl;

   string inVal;
   while( cin >> inVal) cout << isbn(inVal) << endl;

   cout << "End of program 4 by team RF" << endl;
   return 0;
}
