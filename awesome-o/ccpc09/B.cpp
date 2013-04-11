//
// Note that if two ants collide, it must occur at intervals of half units
// of time.
//
// The idea is that we need to simulate half a step at a time.  Also, we
// need to remember that there are now twice as many locations where ants
// can be.
//
// At each half step, each ant moves based on its direction.  There
// can be at most 2 ants ending at the same location.  If there is
// only 1, nothing more needs to be done.  Otherwise, we flip their
// directions before the next step.  It is not clear what should the
// output be if this happens at the last step...but that will never
// happen.  If you do an "ant exchange argument" (every time two ants
// bump into each other you just pretend that they cross each other
// instead of bounce back), then after N steps every ant will end up
// at the original location.  Therefore at the end of N steps all ants
// will be at distinct locations even though they may not be where
// they started.
//

#include <iostream>
#include <algorithm>

using namespace std;

// information to store for each ant
struct Ant {
  int loc;        // its current location (0..N-1)
  int dir;        // 0 for clockwise, 1 for counterclockwise
  int label;      // its label at the beginning (0..N-1)
  
  void move(int N)
  {
    // counterclockwise == clockwise 2*N-1 steps
    // using positive numbers avoid potential problems with %
    int inc = (dir) ? 2*N-1 : 1;
    loc = (loc + inc) % (2*N);
  }
  
  void flip()
  {
    dir = 1 - dir;
  }
};

// simulate one half step.  If two ants end up at the same location at the
// end of this time step, we will flip their directions (pretend that we just
// bumped epsilon units of time earlier).
void simulate(int N, Ant ant[])
{
  int count[200];      // how many ants end up at each location
  int label[200][2];   // which ant are at each location (at most 2)
  fill(count, count+2*N, 0);

  // move everyone
  for (int i = 0; i < N; i++) {
    ant[i].move(N);
    label[ant[i].loc][count[ant[i].loc]++] = i;
  }

  // see which ones collided and change their directions
  for (int i = 0; i < 2*N; i++) {
    if (count[i] != 2) continue;
    ant[label[i][0]].flip();
    ant[label[i][1]].flip();
  }
}

// print the result
void print(int N, Ant ant[])
{
  for (int i = 0; i < N; i++) {
    if (i) cout << ' ';
    cout << ant[i].loc/2 << ' ' << ant[i].dir;
  }
  cout << endl;
}

void do_case(void)
{
  int N;
  cin >> N;

  Ant ant[100];
  for (int i = 0; i < N; i++) {
    cin >> ant[i].dir;
    ant[i].loc = 2*i;      // remember that we have doubled the locations now
    ant[i].label = i;
  }

  for (int step = 0; step < 2*N; step++) {
    simulate(N, ant);
  }

  print(N, ant);
}

int main(void)
{
  int C;

  cin >> C;
  while (C-- > 0) {
    do_case();
  }
  return 0;
}
