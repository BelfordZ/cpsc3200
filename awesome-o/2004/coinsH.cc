#include <fstream>

using namespace std;

#define MAX_DAYS 10000
int answer[MAX_DAYS+1];

int main(void)
{
  int N, i, j;
  ifstream in("coins.in");
  ofstream out("coins.out");

  answer[0] = 0;
  for (N = i = 1; i <= MAX_DAYS; i += N, N++) {
    for (j = 0; j < N && i+j <= MAX_DAYS; j++) {
      answer[i+j] = answer[i+j-1] + N;
    }
  }

  while (in >> N && N > 0) {
    out << N << " " << answer[N] << endl;
  }
  return 0;
}
