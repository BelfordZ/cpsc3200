/* Howard Cheng */

#include <fstream>
#include <string>

using namespace std;

ifstream in("dance.in");
ofstream out("dance.out");

#define MAX_STEP 1000

bool rule1(string dance[MAX_STEP], int n)
{
  int i;
  bool ret = false;
  for (i = 0; i < n; i++) {
    if (dance[i] != "dip") continue;
    if (!((i >= 2 && dance[i-2] == "jiggle") ||
	  (i >= 1 && dance[i-1] == "jiggle") ||
	  (i < n-1 && dance[i+1] == "twirl"))) {
      dance[i] = "DIP";
      ret = true;
    }
  }
  return ret;
}

bool rule2(string dance[MAX_STEP], int n)
{
  return !(n >= 3 && dance[n-3] == "clap" && 
	   dance[n-2] == "stomp" &&
	   dance[n-1] == "clap");
}

bool rule3(string dance[MAX_STEP], int n)
{
  bool twirl = false, hop = false;
  int i;

  for (i = 0; i < n; i++) {
    if (dance[i] == "twirl") twirl = 1;
    if (dance[i] == "hop") hop = 1;
  }
  return twirl && !hop;
}

bool rule4(string dance[MAX_STEP], int n)
{
  return n >= 1 && dance[0] == "jiggle";
}

bool rule5(string dance[MAX_STEP], int n)
{
  int i;
  for (i = 0; i < n; i++) {
    if (dance[i] == "dip") {
      return 0;
    }
  }
  return 1;
}

int main(void)
{
  string dance[MAX_STEP];
  string line;
  bool rule[6];
  int n, i;
  unsigned int pos;
  int errors;

  while (getline(in, line)) {
    n = 0;
    while ((pos = line.find(' ')) != string::npos) {
      dance[n++] = line.substr(0, pos);
      line.erase(0, pos+1);
    }
    if (line.length() > 0) {
      dance[n++] = line;
    }
    errors = 0;
    errors += rule[2] = rule2(dance, n);
    errors += rule[3] = rule3(dance, n);
    errors += rule[4] = rule4(dance, n);
    errors += rule[5] = rule5(dance, n);
    errors += rule[1] = rule1(dance, n);

    out << "form ";
    if (errors) {
      out << "error";
      if (errors > 1) {
	out << "s";
      }
      out << " ";
      for (i = 1; i <= 5; i++) {
	if (rule[i]) {
	  out << i;
	  if (errors > 2) {
	    out << ", ";
	  }
	  if (errors == 2) {
	    out << " and ";
	  }
	  errors--;
	}
      }
      out << ":";
    } else {
      out << "ok:";
    }

    for (i = 0; i < n; i++) {
      out << " " << dance[i];
    }
    out << endl;
  }

  return 0;
}
