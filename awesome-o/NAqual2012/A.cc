// just do it.  Make sure we normalize to lowercase.

#include <iostream>
#include <cctype>
#include <string>

using namespace std;

int main()
{
  string line;
  while (getline(cin, line)) {
    for (int i = 0; i < line.length(); i++) {
      line[i] = tolower(line[i]);
    }
    cout << ((line.find("problem") != string::npos) ? "yes" : "no") << endl;
  }

  return 0;
}
