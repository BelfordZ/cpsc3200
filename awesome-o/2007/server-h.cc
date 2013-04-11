#include <fstream>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<long long, long long> Coord;

const int MAX_N = 1000;
Coord outlet[MAX_N];
int dist[MAX_N];
int n;
int src, dest;
double len1, len2, len_sq;

long long dist_sq(Coord c1, Coord c2)
{
  return (c1.first-c2.first)*(c1.first-c2.first) +
    (c1.second-c2.second)*(c1.second-c2.second);
}

int main(void)
{
  ifstream in("server.in");
  ofstream out("server.out");

  int C;
  in >> C;
  while (C-- > 0) {
    in >> n >> src >> dest >> len1 >> len2;
    src--;
    dest--;
    for (int i = 0; i < n; i++) {
      in >> outlet[i].first >> outlet[i].second;
    }
    fill(dist, dist+n, -1);
    len_sq = (len1 + len2) * (len1 + len2);

    queue<int> q;
    q.push(src);
    dist[src] = 0;
    while (!q.empty()) {
      int curr = q.front();
      q.pop();
      for (int i = 0; i < n; i++) {
	if (dist[i] == -1 && i != curr && 
	    len_sq >= dist_sq(outlet[i], outlet[curr])) {
	  dist[i] = dist[curr]+1;
	  q.push(i);
	}
      }
    }
    if (dist[dest] >= 0) {
      out << dist[dest] << endl;
    } else {
      out << "Impossible" << endl;
    }
  }

  return 0;
}
