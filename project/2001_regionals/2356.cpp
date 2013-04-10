#include <iostream>
#include <string>
#include <stack>
#include <sstream>

using namespace std;

int main() {
   int numTests = 0;
   cin >> numTests;
   string tmp;
   getline(cin, tmp);
   getline(cin, tmp);
   for (int i=0; i<numTests; i++) {
      string inputLine;
      stack<string> backStack;
      stack<string> forStack;
      string currentPage = "http://www.acm.org/";
      if (i != 0) { cout << endl; }

      while(getline(cin, inputLine)) {
	 if (inputLine == "") {
	    break;
	 }
	 else {
	    stringstream ss(inputLine);
	    string inputBuffer;
	    ss >> inputBuffer;

	    if (inputBuffer == "VISIT") {
	       backStack.push(currentPage);
	       ss >> currentPage;
	       cout << currentPage << endl;
	       while (!forStack.empty()) {
		  forStack.pop();
	       }	       
	    }
	    if(inputBuffer == "BACK") {
	       if (!backStack.empty()) {
		  forStack.push(currentPage);
		  currentPage = backStack.top();
		  backStack.pop();
		  cout << currentPage << endl;
	       }
	       else {
		  cout << "Ignored" << endl;
	       }
	    }
	    if(inputBuffer == "FORWARD") {
	       if (!forStack.empty()) {
		  backStack.push(currentPage);
		  currentPage = forStack.top();
		  forStack.pop();
		  cout << currentPage << endl;
	       }
	       else {
		  cout << "Ignored" << endl;
	       }
	    }
	    if(inputBuffer == "QUIT") {
	    }
	 }
      }
   }
}
	 
	 
	
