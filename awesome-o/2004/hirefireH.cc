#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

map<string, vector<string> > tree;
map<string, string> parent;
string root;

ifstream in("hirefire.in");
ofstream out("hirefire.out");

void print_tree(string root, int pluses)
{
  for (unsigned int i = 0; i < tree[root].size(); i++) {
    for (int j = 0; j < pluses; j++) {
      out << "+";
    }
    out << tree[root][i] << endl;
    print_tree(tree[root][i], pluses+1);
  }
}

void fire(string x)
{
  string p = parent[x];

  vector<string>::iterator vp;
  for (vp = tree[p].begin(); vp != tree[p].end() && *vp != x; ++vp)
    ;
  assert(vp != tree[p].end());
  while (tree[x].size() > 0) {
    string child = tree[x][0];
    vector<string> temp = tree[x];
    tree[x] = tree[child];
    tree[child] = temp;

    parent[child] = p;
    *vp = child;

    tree[child][0] = x;
    for (unsigned int i = 0; i < tree[child].size(); i++) {
      parent[tree[child][i]] = child;
    }
    for (unsigned int i = 0; i < tree[x].size(); i++) {
      parent[tree[x][i]] = x;
    }

    p = child;
    vp = tree[p].begin();
  }

  tree.erase(x);
  tree[p].erase(vp);
}

int main(void)
{
  string cmd, op1, op2;

  root = "";
  in >> op1;
  tree[root].push_back(op1);
  parent[op1] = root;

  while (in >> cmd) {
    if (cmd == "print") {
      print_tree(root, 0);
      for (int i = 0; i < 60; i++) {
	out << "-";
      }
      out << endl;
    } else if (cmd == "fire") {
      in >> op1;
      fire(op1);
    } else {
      op1 = cmd;
      in >> cmd >> op2;
      assert(cmd == "hires");
      tree[op1].push_back(op2);
      parent[op2] = op1;
    }
  }

  return 0;
}
