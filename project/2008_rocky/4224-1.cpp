/* Howard Cheng */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <cassert>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream in("when.in");
ofstream out("when.out");

map<string,int> vars;

const int MAX_EXPR = 100000000;
const int MIN_EXPR = -100000000;
const int MAX_STMT = 100000;

int set_count = 0;
int print_count = 0;

void clean_var(string &name)
{
  int i;
  
  for (i = name.length()-1; i >= 0; i--) {
    if (name[i] != ' ') continue;
    if (i > 0 && name[i-1] == ' ') {
      name.erase(i,1);
    } else {
      name[i] = '_';
    }
  }
}

void clean(string &s)
{
  while (s.length() > 0 && isspace(s[s.length()-1])) {
    s.erase(s.length()-1, 1);
  }
  while (s.length() > 0 && isspace(s[0])) {
    s.erase(0, 1);
  }
}

class Expression {
private:
  string expr;

  int evaluate(string expr) const
  {
    int ans;

    clean(expr);
    if (expr[0] == '(') {
      assert(expr[expr.length()-1] == ')');
      expr.erase(expr.length()-1,1);
      expr.erase(0,1);
      clean(expr);

      int pcount = 0, dcount = 0;
      unsigned int i;
      for (i = 0; i < expr.length(); i++) {
	if (expr[i] == '(') pcount++;
	else if (expr[i] == ')') pcount--;
	else if (expr[i] == '$') dcount++;
	if (!pcount && (dcount % 2 == 0) &&
	    (expr[i] == '<' || expr[i] == '+' || expr[i] == '-' ||
	     expr.find("and", i) == i || expr.find("or", i) == i ||
	     expr.find("xor", i) == i)) {
	  break;
	}
      }
      assert(1 <= i && i < expr.length());
      int left = evaluate(expr.substr(0, i));
      int right;
      if (expr.find("<", i) == i) {
	right = evaluate(expr.substr(i+1, expr.length()-i-1));
	return (left < right) ? 1 : 0;
      } else if (expr.find("+", i) == i) {
	right = evaluate(expr.substr(i+1, expr.length()-i-1));
	assert( MIN_EXPR <= left+right && left+right <= MAX_EXPR);
	return left+right;
      } else if (expr.find("-", i) == i) {
	right = evaluate(expr.substr(i+1, expr.length()-i-1));
	assert( MIN_EXPR <= left-right && left-right <= MAX_EXPR);
	return left-right;
      } else if (expr.find("and", i) == i) {
	right = evaluate(expr.substr(i+3, expr.length()-i-3));
	return (left && right) ? 1 : 0;
      } else if (expr.find("or", i) == i) {
	right = evaluate(expr.substr(i+2, expr.length()-i-2));
	return (left || right) ? 1 : 0;
      } else if (expr.find("xor", i) == i) {
	right = evaluate(expr.substr(i+3, expr.length()-i-3));
	return ((left && !right) || (!left && right)) ? 1 : 0;
      }
    } else if (expr[0] == '$') {
      for (unsigned int i = 1; i < expr.length()-1; i++) {
	assert(expr[i] != '$');
      }
      assert(expr[expr.length()-1] == '$');
      clean_var(expr);
      return vars[expr];
    } else {
      ans = 0;
      for (unsigned int i = 0; i < expr.length(); i++) {
	assert(isdigit(expr[i]));
	ans = ans*10 + (expr[i]-'0');
      }
      return ans;
    }
    return -1;      // keep compiler happy
  }
  
public:
  Expression(const string &line)
    : expr(line)
  {
  }

  int evaluate() const 
  {
    return evaluate(expr);
  }

  friend ostream &operator<<(ostream &os, const Expression &e);
};

ostream &operator<<(ostream &os, const Expression &e)
{
  return os << e.expr;
}

class Statement {

public:
  virtual void print(ostream &os) const = 0;
  virtual void run() const = 0;
};

class Print : public Statement {
private:
  vector<Expression> expr;
public:
  Print(string expr_list)
  {
    unsigned int pos;

    while ((pos = expr_list.find(",")) != string::npos) {
      expr.push_back(Expression(expr_list.substr(0,pos)));
      expr_list.erase(0,pos+1);
    }
    if (expr_list.length() > 0) {
      expr.push_back(Expression(expr_list));
    }
  }

  virtual void print(ostream &os) const {
    os << "PRINT ";
    for (unsigned int i = 0; i < expr.size(); i++) {
      if (i) os << ", ";
      os << expr[i];
    }
  }    

  virtual void run() const {
    for (unsigned int i = 0; i < expr.size(); i++) {
      if (i) out << ",";
      out << expr[i].evaluate();
    }
    out << endl;
    print_count++;
  }

};

class Set : public Statement {
private:
  vector<string> varname;
  vector<Expression> expr;

  void parse_assign(string assign)
  {
    unsigned int pos = assign.find('=');
    string var = assign.substr(0,pos);
    clean(var);
    clean_var(var);
    varname.push_back(var);
    assign.erase(0, pos+1);
    clean(assign);
    expr.push_back(Expression(assign));
  }

public:
  Set(string assign_list)
  {
    unsigned int pos;

    while ((pos = assign_list.find(",")) != string::npos) {
      parse_assign(assign_list.substr(0,pos));
      assign_list.erase(0,pos+1);
    }
    if (assign_list.length() > 0) {
      parse_assign(assign_list);
    }
    
    // check that no two assignments have the same RHS
    for (unsigned int i = 0; i < varname.size(); i++) {
      for (unsigned int j = i+1; j < varname.size(); j++) {
	assert(varname[i] != varname[j]);
      }
    }
  }

  virtual void print(ostream &os) const {
    os << "SET ";
    for (unsigned int i = 0; i < varname.size(); i++) {
      if (i) os << ", ";
      os << varname[i] << "=" << expr[i];
    }
  }   
  
  virtual void run() const {
    vector<int> vals(varname.size());
    
    for (unsigned int i = 0; i < varname.size(); i++) {
      vals[i] = expr[i].evaluate();
    }
    for (unsigned int i = 0; i < varname.size(); i++) {
      vars[varname[i]] = vals[i];
    }
    set_count++;
  }
};

class When {
private:
  Expression condition;
  vector<Statement*> statement;
  unsigned int index; // index to the ready statement
  bool active;

public:
  When()
    : condition("123")  // some dummy expression
  {
  }

  ~When() {
    clear();
  }

  void clear() {
    for (unsigned int i = 0; i < statement.size(); i++) {
      //delete statement[i];
    }
    statement.clear();
    index = 0;
    active = false;
  }

  bool isActive() const {
    return active;
  }

  bool currentlyActive() {
    if (condition.evaluate() != 0) {
      index = 0;
      active = true;
      return true;
    } else {
      active = false;
      return false;
    }
  }

  bool execute() {
    assert(0 <= index && index < statement.size());
    statement[index++]->run();
    return (active = (index < statement.size()));
  }

  void add_statement(string line)
  {
    if (line.find("print ") == 0) {
      line.erase(0, 6);
      clean(line);
      statement.push_back(new Print(line));
    } else {
      assert(line.find("set ") == 0);
      line.erase(0, 4);
      clean(line);
      statement.push_back(new Set(line));
    }
  }

  friend istream &operator>>(istream &is, When &w);
  friend ostream &operator<<(ostream &os, const When &w);
};

istream &readlower(istream &is, string &s)
{
  if (!getline(is, s)) {
    return is;
  }
  for (unsigned int i = 0; i < s.length(); i++) {
    s[i] = tolower(s[i]);
  }
  clean(s);
  return is;
}

istream &operator>>(istream &is, When &w)
{
  string line;

  if (!readlower(is, line)) {
    return is;
  }
  int pos = line.find("when ");
  assert(pos == 0);
  line.erase(0, 5);
  clean(line);
  w.condition = Expression(line);

  w.clear();
  while (readlower(is, line) && line != "end when") {
    w.add_statement(line);
  }
  assert(is && line == "end when");
  return is;
}

ostream &operator<<(ostream &os, const When &w)
{
  os << "Condition: " << w.condition << endl;
  os << "Statements: " << endl;
  for (unsigned int i = 0; i < w.statement.size(); i++) {
    os << "  ";
    w.statement[i]->print(os);
    os << endl;
  }
  return os;
}

int main(void)
{
  vector<When> clause;
  When w;

  while (in >> w) {
    clause.push_back(w);
  }

  vector<int> active;
  unsigned int current = 0;
  while (true) {
    // evaluate non-active ones and add to end of list of actives
    for (unsigned int i = 0; i < clause.size(); i++) {
      if (clause[i].isActive()) continue;
      if (clause[i].currentlyActive()) {
	active.push_back(i);
      }
    }

    // if active list is empty, quit
    if (active.size() == 0) 
      break;
    
    // execute round-robin
    if (!clause[active[current]].execute()) {
      active.erase(active.begin()+current);
    } else {
      current++;
    }
    
    if (current >= active.size()) {
      current = 0;
    }
    assert(set_count <= MAX_STMT && print_count <= MAX_STMT);
  }



  return 0;
}
