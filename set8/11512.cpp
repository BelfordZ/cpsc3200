#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;
//we use a suffix array here. (pulled from Howards Code library)
#define GetI() (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2)
bool leq(int a1, int a2, int b1, int b2){return(a1 < b1 || a1 == b1 && a2 <= b2);}                        
bool leq(int a1, int a2, int a3, int b1, int b2, int b3){return(a1 < b1 || a1 == b1 && leq(a2,a3, b2,b3));}
void radixPass(int* a, int* b, int* r, int n, int K) {int* c = new int[K + 1];fill(c, c+K+1, 0);for (int i = 0;  i < n;  i++) c[r[a[i]]]++;for (int i = 0, sum = 0;  i <= K;  i++) {int t = c[i];  c[i] = sum;  sum += t;}for (int i = 0;  i < n;  i++) b[c[r[a[i]]]++] = a[i]; delete [] c;}
void sarray_int(int* s, int* SA, int n, int K) {int n0=(n+2)/3, n1=(n+1)/3, n2=n/3, n02=n0+n2; int* s12  = new int[n02 + 3];  s12[n02]= s12[n02+1]= s12[n02+2]=0;int* SA12 = new int[n02 + 3]; SA12[n02]=SA12[n02+1]=SA12[n02+2]=0; int* s0 = new int[n0];  int* SA0 = new int[n0];for (int i=0, j=0;  i < n+(n0-n1);  i++) if (i%3 != 0) s12[j++] = i; radixPass(s12 , SA12, s+2, n02, K);radixPass(SA12, s12 , s+1, n02, K); radixPass(s12 , SA12, s  , n02, K);int name = 0, c0 = -1, c1 = -1, c2 = -1; for (int i = 0;  i < n02;  i++) { if (s[SA12[i]] != c0 || s[SA12[i]+1] != c1 || s[SA12[i]+2] != c2) { name++;  c0 = s[SA12[i]];  c1 = s[SA12[i]+1];  c2 = s[SA12[i]+2]; } if (SA12[i] % 3 == 1) { s12[SA12[i]/3]= name; } else { s12[SA12[i]/3 + n0] = name; }} if (name < n02) { sarray_int(s12, SA12, n02, name); for (int i = 0;i < n02;  i++) s12[SA12[i]] = i + 1;} else for (int i = 0;  i < n02;  i++) SA12[s12[i] - 1] = i; for (int i=0, j=0;  i < n02;  i++) if (SA12[i] < n0) s0[j++] = 3*SA12[i]; radixPass(s0, SA0, s, n0, K);for (int p=0,  t=n0-n1,k=0;k<n;k++){int i = GetI();int j = SA0[p]; if (SA12[t] < n0 ? leq(s[i],s12[SA12[t] + n0], s[j],s12[j/3]) : leq(s[i],s[i+1],s12[SA12[t]-n0+1], s[j],s[j+1],s12[j/3+n0])){ SA[k] = i;  t++; if (t == n02) {for (k++;  p < n0;  p++, k++) SA[k] = SA0[p]; } } else { SA[k] = j;  p++; if (p == n0)  {for (k++;  t < n02;  t++, k++) SA[k] = GetI(); }}}delete [] s12; delete [] SA12; delete [] SA0; delete [] s0; }
void build_sarray(string str, int sarray[]){int n = str.length();if (n <= 1) {for (int i = 0; i < n; i++) { sarray[i] = i; }return;}int *s = new int[n+3];int *SA = new int[n+3];for (int i = 0; i < n; i++) {s[i] = (int)str[i] - CHAR_MIN + 1; } s[n] = s[n+1] = s[n+2] = 0; sarray_int(s, SA, n, 256); copy(SA, SA+n, sarray);  delete[] s; delete[] SA;}
void compute_lcp(string str, int sarray[], int lcp[]){int n = str.length();int *rank = new int[n];for (int i = 0; i < n; i++) {rank[sarray[i]] = i;}int h = 0;for (int i = 0; i < n; i++) {int k = rank[i]; if (k == 0) {lcp[k] = -1;} else {int j = sarray[k-1]; while (i + h < n && j + h < n && str[i+h] == str[j+h]) {h++;} lcp[k] = h; }if (h > 0) { h--; }} lcp[0] = 0;  delete[] rank;}
/*
 * build suffix array -> sarray[0...n-1] where sarray[x]== index to start of ith index xEZ x<n
 * build LCP array -> lcp[0...n-1] where lcp[x]== number of common substrings with lcp[x-1] (lcp[0]=0) xEZ x<n
 * get max from LCP
 *      (maxLCP == largest substring appearing >=2 times)
 */

int main() {
   int numTests = 0, sarray[1000], lcp[1000];
   cin >> numTests;

   for (int i=0; i<numTests; i++) {
      string line;
      cin >> line;

      build_sarray(line, sarray);compute_lcp(line,sarray, lcp);

      int numAppearences = 0, max = 0;
      string commonSubstr; //current longest prefix of suffixes.

      for (int j=0; j<line.length(); j++) {
	 //if this lcprefix of the suffix is new max, set new max, and number of appearences must be 2
	 if ( (max < lcp[j]) && (max = lcp[j]) && (numAppearences = 2) )
	    commonSubstr = line.substr(sarray[j-1], lcp[j]);
	 else if ( (max == lcp[j]) && (lcp[j] != 0) && (line.substr(sarray[j-1], lcp[j]) == commonSubstr) )
	    numAppearences++;  
	 //otherwise, if lcprefix was the same as max, but max isn't 0,
	 //   this one has a greater numAppearences
      }
      if (numAppearences)
	 cout << commonSubstr << " " << numAppearences;
      else
	 cout << "No repetitions found!";
      cout << endl;
   }
   return 0;
}
