#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <set>
#include <cassert>

using namespace std;

int M, N, T;

ifstream in("hourglass.in");
ofstream out("hourglass.out");

// each state is represented by a tuple (t,(t1,t2)) where
// t = time so far, ti = time left in hour glass i
//
// Note that the state space is not that big, because we are only
// allowed to flip when one expires.
typedef pair<int, pair<int, int> > State;


ostream &operator<<(ostream &os, State s)
{
  return os << "(" << s.first << ", (" << s.second.first << ", "
	    << s.second.second << "))";
}

void print(State q, map<State, State> &from, map<State, int> &type)
{
  State parent = from[q];

  //  cout << "from[" << q << "] = " << from[q] << endl;
  if (parent.first < 0) {
    return;
  }
  print(parent, from, type);
  out << parent.first << ": ";
  if (type[q] == 1) {
    out << M << endl;
  } else if (type[q] == 2) {
    out << N << endl;
  } else if (type[q] == 3) {
    out << M << "," << N << endl;
  } else {
    assert(0);
  }
}

void update(State prev, State &next, set<State> &visited, 
	    map<State, State> &from, queue<State> &Q, map<State, int> &type, 
	    int typecode)
{
  if (next.first > T) {
    // no need to do anything more
    return;
  }

  if (visited.find(next) != visited.end()) {
    // already visited, no need to visit again
    return;
  }

  if (typecode) {
    from[next] = prev;
    type[next] = typecode;
    Q.push(next);
    visited.insert(next);
    //    cout << "  Inserting " << next << endl;
  }
}

void nextstates(State prev, State next, set<State> &visited, 
		map<State, State> &from, queue<State> &Q, 
		map<State, int> &type, int typecode)
{
  //  cout << "next = " << next << endl;
  assert(next.second.first || next.second.second);
  
  State n;

  // let the first one expires
  if (next.second.first) {
    n = next;
    n.first += n.second.first;
    n.second.second -= n.second.first;
    n.second.first = 0;
    n.second.second = max(0, n.second.second);
    update(prev, n, visited, from, Q, type, typecode);
  }

  // let the second one expires
  if (next.second.second) {
    n = next;
    n.first += n.second.second;
    n.second.first -= n.second.second;
    n.second.second = 0;
    n.second.first = max(0, n.second.first);
    update(prev, n, visited, from, Q, type, typecode);
  }
}


void flip(map<State, State> &from, map<State, int> &type, 
	   queue<State> &Q, set<State> &visited, State q)
{

  //  cout << "Exploring " << q << endl;
  State next;
  
  if (q.first > 0) {
    // flip the first one
    next = q;
    next.second.first = M - next.second.first;
    nextstates(q, next, visited, from, Q, type, 1);
  
    // flip the second one
    next = q;
    next.second.second = N - next.second.second;
    nextstates(q, next, visited, from, Q, type, 2);
  }

  // flip both
  next = q;
  next.second = make_pair<int, int>(M - next.second.first, 
				    N - next.second.second);
  nextstates(q, next, visited, from, Q, type, 3);
}

void solve_case(void)
{
  // from is the "parent state" in the shortest path tree to get
  // there
  map<State, State> from;

  // type indicates what type of flips the parent edge is
  // 0 = no flip, 1 = flip glass 1, 2 = flip glass 2, 3 = flip both
  map<State, int> type;

  // the queue vertices
  queue<State> Q;

  // have I seen this
  set<State> visited;

  State v0, next, q;

  v0.first = 0;  v0.second = make_pair<int,int>(0,0);

  Q.push(v0);
  from[v0].first = -1;
  type[v0] = 0;
  visited.insert(v0);

  while (!Q.empty()) {
    q = Q.front();
    Q.pop();
    if (q.first == T) {
      break;
    }
    flip(from, type, Q, visited, q);
  }

  if (q.first == T) {
    print(q, from, type);
  } else {
    out << "Impossible!" << endl;
  }
  out << "----------" << endl;
}

int main(void)
{
  while (in >> M >> N >> T && (M || N || T)) {
#ifdef DEBUG
    cout << "M, N, T = " << M << ", " << N << ", " << T << endl;
#endif
    solve_case();
  }
  return 0;
}
