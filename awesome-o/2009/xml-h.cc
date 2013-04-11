#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

enum Type {
  PLAIN,     // case 1
  ESC,       // cases 2-3
  OPEN,      // case 4
  ALONE,     // case 5
  CLOSE,     // case 6
  END,       // no more tokens
  BAD        // invalid
};

struct Token
{
  Type type;
  int len;     // number of characters in the token
  string tag;


  Token(Type t = BAD, int l = 1, const string &s = "")
    : type(t), len(l), tag(s) { }
};

bool isloweralnum(char c)
{
  return islower(c) || isdigit(c);
}

Token nextToken(const string &doc, string::size_type index)
{
  if (index >= doc.length()) {
    return Token(END);
  }

  // case 1
  if (!(32 <= doc[index] && ((int)doc[index]) <= 127)) {
    return Token(BAD);
  }

  if (doc[index] != '<' && doc[index] != '>' && doc[index] != '&') {
    return Token(PLAIN);
  }

  // cases 2-3
  if (doc[index] == '&') {
    // check &lt;, &gt;, &amp;
    if (doc.find("&lt;", index) == index ||
	doc.find("&gt;", index) == index) {
      return Token(ESC, 4);
    } else if (doc.find("&amp;", index) == index) {
      return Token(ESC, 5);
    }

    // check &xHEX;
    if (index+1 < doc.length() && doc[index+1] == 'x') {
      int count = 0;
      bool done = false;
      for (string::size_type i = index+2; i < doc.length(); i++) {
	if (doc[i] == ';') {
	  done = true;
	  break;
	}
	if (!isxdigit(doc[i])) {
	  return Token(BAD);
	}
	count++;
      }
      if (done && count > 0 && count % 2 == 0) {
	return Token(ESC, count+3);
      }
      return Token(BAD);
    }

    // bad &
    return Token(BAD);
  }

  // cases 4-6
  if (doc[index] == '<') {
    if (index+1 >= doc.length()) {
      return Token(BAD);
    }

    // case 6
    if (doc[index+1] == '/') {
      string tag;
      int len = 0;
      bool done = false;
      for (string::size_type i = index+2; i < doc.length(); i++) {
	if (doc[i] == '>') {
	  done = true;
	  break;
	}
	if (isloweralnum(doc[i])) {
	  len++;
	  tag += doc[i];
	} else {
	  return Token(BAD);
	}
      }
      return Token(CLOSE, len+3, tag);

    }

    // cases 4-5
    string tag;
    int len = 0;
    for (string::size_type i = index+1; i < doc.length(); i++) {
      if (doc[i] == '>') {
	return Token(OPEN, len+2, tag);
      }
      if (doc[i] == '/') {
	if (i+1 < doc.length() && doc[i+1] == '>') {
	  return Token(ALONE, len+3, tag);
	} else {
	  return Token(BAD);
	}
      }
      if (isloweralnum(doc[i])) {
	len++;
	tag += doc[i];
      } else {
	return Token(BAD);
      }
    }
    return Token(BAD);
  }

  return Token(BAD);
}

bool valid(const string &doc)
{
  stack<string> context;
  string::size_type index = 0;

  Token t = nextToken(doc, index);
  while (t.type != END) {
    if (t.type == BAD) {
      return false;
    }

    if (t.type == OPEN) {
      if (t.tag.length() > 0) {
	context.push(t.tag);
      } else {
	return false;
      }
    } else if (t.type == CLOSE) {
      // are tags case sensitive?
      if (context.empty() || context.top() != t.tag) {
	return false;
      }
      context.pop();
    }

    index += t.len;
    t = nextToken(doc, index);
  }
  
  return context.empty();
}

int main(void)
{
  string doc;

  while (getline(cin, doc)) {
    cout << (valid(doc) ? "valid" : "invalid") << endl;
  }
  return 0;
}
