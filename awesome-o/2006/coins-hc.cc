#include <fstream>
#include <cmath>

using namespace std;

#define EPS 1e-8

int main(void)
{
  int N;
  int w, d;
  int W;
  int norm;

  ifstream in("coins.in");
  ofstream out("coins.out");

  while (in >> N >> w >> d >> W) {
    norm = w*N*(N-1)/2;
    int t =  (norm - W)/d;
    if (t == 0) {
      t = N;
    }
    out << t << endl;
  }
  return 0;
}
