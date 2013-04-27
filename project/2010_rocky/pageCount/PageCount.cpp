// Problem 4886
// Solution By Zach Belford

// boolean array holds places visited. These problems ones sure
// make you hate yourself when it doesn't work yet it is so simple.
// well as Frank Sinatra would say had he been a programmer,
// 'thats adhocccc'
/*
 * sources (other than the usual text book n stuff):
 * http://www.daniweb.com/software-development/cpp/threads/121510/csv-file-to-array-c
 */
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

int pageMax = 0;
int n_ary_Encode[1001];

pair<int, int> makeValidPair(string notCsv){
   string low, high;
   istringstream is(notCsv);
   int lowi, highi;
   
   // if its a single digit pair just make them equal.
   getline(is, low, '-');
   istringstream ( low ) >> lowi;
   if (!getline(is, high, '-'))
      highi=lowi;
   else
      istringstream ( high ) >> highi;

   if (lowi > highi || lowi > pageMax) {return make_pair(-1, 0);} // ignore low > high
   if (highi > pageMax) { highi = pageMax; }
   //cout << lowi << "-" << highi << endl;
   return make_pair(lowi, highi);
};
void clear() {
   for (int i=0; i<1001; i++)
      n_ary_Encode[i] = 0;
}
int main() {
   string ranges;
   int lo =0 ;
   clear();
   while (cin>>pageMax && getline(cin, ranges) && getline(cin, ranges) && pageMax!=0) {
      vector<string> csvNoMore;
      istringstream iss(ranges);
      //split from the comma, push it to array.
      while(true) {
	 string tmp;
	 if (!getline(iss, tmp, ',')) break;
	 csvNoMore.push_back(tmp);
      }
      for (int i=0; i<csvNoMore.size(); i++) {
	 pair<int,int> tmp = makeValidPair(csvNoMore[i]);
	 if (tmp.first == -1) {;}
	 else 
	    for (int j=tmp.first; j<=tmp.second; j++) 
	       n_ary_Encode[j] = 1;
      }
      int answer = 0;
      for (int i=0; i<=1001; i++) {
	 if (n_ary_Encode[i]) answer++;
      }
      //cout << lo << "--" << answer << endl;
      cout << answer << endl;
      lo++;
      clear();
      ranges = "";
      pageMax = 0;
   }
   return 0;
}

/*
 * sources:
 * http://www.daniweb.com/software-development/cpp/threads/121510/csv-file-to-array-c
 */
