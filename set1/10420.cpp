#include <iostream>
#include <iterator>
#include <string>
#include <map>
#include <set>
using namespace std;

int main()
{
   int n=0;
   cin >> n; //get number of lines
   
   string conquest="";
   getline (cin,conquest); //clear stream
   
   map <string,set<string> > listOfConquests;
   
   for (int i=0; i<n; i++) //for each conquest
   {
      getline (cin,conquest);
      
      int firstSpace = conquest.find(' '); //split the country from the trick
      string country = conquest.substr(0, firstSpace);
      string trick = conquest.substr(firstSpace);
      
      listOfConquests[country].insert(trick); //insert her name into unique set
   }
   
   typedef map <string,set<string> >::const_iterator iter; //to iterate map
   for(iter i = listOfConquests.begin(); i != listOfConquests.end(); i++)
   {
      cout<< i->first << " " << i->second.size()<<endl; //print country, and # of tricks
   }
   return 0; 
}
