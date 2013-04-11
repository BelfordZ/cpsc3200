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

class Variable {
private:
  string name;

public:
  Variable(const string &var) 
    : name(var) 
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
  
  const string &getname() const
  {
    return name;
  }

  int &value(void)
  {
    return vars[name];
  }

  int value(void) const
  {
    return vars[name];
  }
};

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
  enum Type { LT, PLUS, MINUS, AND, OR, XOR, VAR, NUM };
  Expression *left, *right;
  Type type;
  Variable *var;
  int value;

  void parse(string expr)
  {
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
      left = new Expression(expr.substr(0, i));
      if (expr.find("<", i) == i) {
	type = LT;
	right = new Expression(expr.substr(i+1, expr.length()-i-1));
      } else if (expr.find("+", i) == i) {
	type = PLUS;
	right = new Expression(expr.substr(i+1, expr.length()-i-1));
      } else if (expr.find("-", i) == i) {
	type = MINUS;
	right = new Expression(expr.substr(i+1, expr.length()-i-1));
      } else if (expr.find("and", i) == i) {
	type = AND;
	right = new Expression(expr.substr(i+3, expr.length()-i-3));
      } else if (expr.find("or", i) == i) {
	type = OR;
	right = new Expression(expr.substr(i+2, expr.length()-i-2));
      } else if (expr.find("xor", i) == i) {
	type = XOR;
	right = new Expression(expr.substr(i+3, expr.length()-i-3));
      }
    } else if (expr[0] == '$') {
      type = VAR;
      var = new Variable(expr);
    } else {
      type = NUM;
      value = 0;
      for (unsigned int i = 0; i < expr.length(); i++) {
	assert(isdigit(expr[i]));
	value = value*10 + (expr[i]-'0');
      }
    }
  }
  
public:
  Expression(const string &line)
  {
    parse(line);
  }

  int evaluate() const 
  {
    int lval, rval;
    switch (type) {
    case LT:
      lval = left->evaluate();
      rval = right->evaluate();
      return (lval < rval);
    case PLUS:
      lval = left->evaluate();
      rval = right->evaluate();
      assert( MIN_EXPR <= lval+rval && lval+rval <= MAX_EXPR);
      return (lval + rval);
    case MINUS:
      lval = left->evaluate();
      rval = right->evaluate();
      assert( MIN_EXPR <= lval-rval && lval-rval <= MAX_EXPR);
      return (lval - rval);
    case AND:
      lval = left->evaluate();
      rval = right->evaluate();
      return (lval && rval);
    case OR:
      lval = left->evaluate();
      rval = right->evaluate();
      return (lval || rval);
    case XOR:
      lval = left->evaluate();
      rval = right->evaluate();
      return (lval && !rval) || (!lval && rval);
    case VAR:
      return var->value();
    case NUM:
      return value;
    default:
      assert(0);
    }
  }
};

class Statement {

public:
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
  vector<Variable *> varname;
  vector<Expression> expr;

  void parse_assign(string assign)
  {
    unsigned int pos = assign.find('=');
    string var = assign.substr(0,pos);
    clean(var);
    varname.push_back(new Variable(var));
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
	assert(varname[i]->getname() != varname[j]->getname());
      }
    }
  }

  virtual void run() const {
    vector<int> vals(varname.size());
    
    for (unsigned int i = 0; i < varname.size(); i++) {
      vals[i] = expr[i].evaluate();
    }
    for (unsigned int i = 0; i < varname.size(); i++) {
      varname[i]->value() = vals[i];
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
