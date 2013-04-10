#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int highest(vector<pair<string, int> > x);
int isWordKey(string word);

int numOfKeys = 0;
int numOfExcuses = 0;
vector<string> keys;
vector<pair<string, int> > excuses;

int main() {
   int iteration = 0;
   while (cin>>numOfKeys>>numOfExcuses) {
      iteration++;
      cout << "Excuse Set #" << iteration << endl;

      keys.clear();
      excuses.clear();
      
      string tmp = "";
      getline(cin, tmp);
      
      for(int i=0; i<numOfKeys; i++) {
	 getline(cin, tmp);
	 keys.push_back(tmp);
      }

      for (int i=0; i<numOfExcuses; i++) {
	 string excuse;
	 getline(cin, excuse);
	 istringstream iss(excuse);

	 string word;
	 int count = 0;
	 
	 while (iss>>word)
	    count += isWordKey(word);
	 
	 pair <string, int> tmpPair(excuse, count);
	 excuses.push_back(tmpPair);
      }
      int maxVal = highest(excuses);
      for (int i=0; i<excuses.size(); i++)
	 if (excuses[i].second == maxVal) 
	    cout << excuses[i].first << endl;
      cout << endl;
   }
}

int isWordKey(string word)
{
   for (int i=0; i<word.size(); i++) {
      if (!isalpha(word[i]))
	 word[i] = ' ';
      else
	 word[i] = tolower(word[i]);
   }

   istringstream tmpiss(word);
   
   int counter = 0;
   while (tmpiss >> word)
   {
      for (int i=0; i<keys.size(); i++)
	 if (word.compare(keys[i]) == 0)
	    counter++;
   }
   return counter;
}

int highest(vector<pair<string, int> > x) {
   int max = 0; 
   for (int i=0; i<x.size(); i++) 
      if (x[i].second > max)
	 max = x[i].second;
   return max;
}
