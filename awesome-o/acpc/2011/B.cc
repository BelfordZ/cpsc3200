// bidirectional search: expand from goal state backwards to 10 moves,
// then search forward from each of the starting state

#include <iostream>
#include <iomanip>
#include <queue>
#include <map>
#include <cassert>

using namespace std;

typedef long long ll;

struct State
{
  int perm[12];

  State()
  {
    for (int i = 0; i < 12; i++) {
      perm[i] = i+1;
    }
  }

  void read()
  {
    for (int i = 0; i < 12; i++) {
      cin >> perm[i];
    }
  }

  void move1()
  {
    int temp = perm[0];
    perm[0] = perm[1];
    perm[1] = perm[2];
    perm[2] = perm[3];
    perm[3] = perm[4];
    perm[4] = perm[5];
    perm[5] = perm[11];
    perm[11] = temp;
  }

  void move2()
  {
    int temp = perm[0];
    perm[0] = perm[11];
    perm[11] = perm[5];
    perm[5] = perm[4];
    perm[4] = perm[3];
    perm[3] = perm[2];
    perm[2] = perm[1];
    perm[1] = temp;
  }

  void move3()
  {
    int temp = perm[5];
    perm[5] = perm[6];
    perm[6] = perm[7];
    perm[7] = perm[8];
    perm[8] = perm[9];
    perm[9] = perm[10];
    perm[10] = perm[11];
    perm[11] = temp;
  }
  
  void move4()
  {
    int temp = perm[5];
    perm[5] = perm[11];
    perm[11] = perm[10];
    perm[10] = perm[9];
    perm[9] = perm[8];
    perm[8] = perm[7];
    perm[7] = perm[6];
    perm[6] = temp;
  }

  void move5()
  {
    int temp = perm[0];
    for (int i = 0; i < 11; i++) {
      perm[i] = perm[i+1];
    }
    perm[11] = temp;
  }
  
  void move6()
  {
    int temp = perm[11];
    for (int i = 11; i >= 1; i--) {
      perm[i] = perm[i-1];
    }
    perm[0] = temp;
  }

  operator ll() const
  {
    ll s = 0;
    
    for (int i = 0; i < 11; i++) {
      s |= ((ll)perm[i] << (4*i));
    }
    return s;
  }

  void print() const
  {
    cout << '(';
    for (int i = 0; i < 12; i++) {
      if (i) cout << ", ";
      cout << setw(2) << perm[i];
    }
    cout << ')' << endl;
  }
};


void add_state(queue<State> &q, map<ll,int> &dist, 
	       const State &next, int currd)
{
  if (dist.find((ll)next) != dist.end()) return;
  dist[(ll)next] = currd + 1;
  q.push(next);
}

map<ll,int> bdist;
void workbackward()
{
  State goal;
  queue<State> backward;

  backward.push(goal);
  bdist[(ll)goal] = 0;

  while (!backward.empty()) {
    State curr = backward.front();
    backward.pop();
    int d = bdist[(ll)curr];
    if (d == 10) {
      cout << bdist.size() << endl;
      return;
    }

    State next = curr;
    
    next.move1();
    add_state(backward, bdist, next, d);
    next = curr;
    next.move2();
    add_state(backward, bdist, next, d);
    next = curr;
    next.move3();
    add_state(backward, bdist, next, d);
    next = curr;
    next.move4();
    add_state(backward, bdist, next, d);
    next = curr;
    next.move5();
    add_state(backward, bdist, next, d);
    next = curr;
    next.move6();
    add_state(backward, bdist, next, d);
  }
}

void solve()
{
  State start;
  start.read();

  queue<State> forward;
  map<ll,int> fdist;
  
  forward.push(start);
  fdist[(ll)start] = 0;

  while (!forward.empty()) {
    State curr = forward.front();
    forward.pop();
    if (bdist.find((ll)curr) != bdist.end()) {
      cout << fdist[(ll)curr] + bdist[(ll)curr] << endl;
      return;
    }
    int d = fdist[(ll)curr];
    State next = curr;
    
    next.move1();
    add_state(forward, fdist, next, d);
    next = curr;
    next.move2();
    add_state(forward, fdist, next, d);
    next = curr;
    next.move3();
    add_state(forward, fdist, next, d);
    next = curr;
    next.move4();
    add_state(forward, fdist, next, d);
    next = curr;
    next.move5();
    add_state(forward, fdist, next, d);
    next = curr;
    next.move6();
    add_state(forward, fdist, next, d);
  }

  assert(false);
}

int main(void)
{
  workbackward();
  
  int N;
  cin >> N;
  while (N--) {
    solve();
  }
  return 0;
}
