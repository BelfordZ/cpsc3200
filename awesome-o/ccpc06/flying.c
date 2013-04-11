#include <stdio.h>
#include <string.h>
#include <assert.h>

char city[100][100];
int flight[100][100];
int best_cost[100][100];
int N, M;
int max_stops;

int cityindex(char *s)
{
  int i;

  for (i = 0; i < N; i++) {
    if (!strcmp(city[i], s)) {
      return i;
    }
  }
  assert(0);
}

int search(int stops)
{
  int ans, i, j, k, temp;

  if (stops > N-2) {
    stops = N-2;
  }

  if (max_stops < stops) {
    if (max_stops < 0) {
      for (i = 0; i < N; i++) {
	best_cost[i][0] = flight[0][i];
      }
      max_stops = 0;
    }

    for (j = max_stops+1; j <= stops; j++) {
      for (i = 0; i < N; i++) {
	best_cost[i][j] = -1;
	for (k = 0; k < i; k++) {
	  if (best_cost[k][j-1] == -1 || flight[k][i] == -1) continue;
	  temp = best_cost[k][j-1] + flight[k][i];
	  if (best_cost[i][j] == -1 || temp < best_cost[i][j]) {
	    best_cost[i][j] = temp;
	  }
	}
      }
    }

    max_stops = stops;
  }
  
  ans = -1;
  for (i = 0; i <= stops; i++) {
    if (ans == -1 || (best_cost[N-1][i] >= 0 && best_cost[N-1][i] < ans)) {
      ans = best_cost[N-1][i];
    }
  }
  return ans;
}

int main(void)
{
  FILE *in, *out;
  int C, Q, i, j, k, cost, stops, i1, i2;
  char c1[100], c2[100];

  in = fopen("flying.in", "r");
  out = fopen("flying.out", "w");
  

  fscanf(in, "%d", &C);
  for (i = 0; i < C; i++) {
    max_stops = -1;
    fprintf(out, "%sScenario #%d\n", (i ? "\n" : ""), i+1);

    fscanf(in, "%d", &N);
    for (j = 0; j < N; j++) {
      fscanf(in, "%s", city[j]);
    }

    for (j = 0; j < N; j++) {
      for (k = 0; k < N; k++) {
	flight[j][k] = -1;
      }
    }

    fscanf(in, "%d", &M);
    for (j = 0; j < M; j++) {
      fscanf(in, "%s %s %d", c1, c2, &cost);
      i1 = cityindex(c1);
      i2 = cityindex(c2);
      if (flight[i1][i2] == -1 || cost < flight[i1][i2]) {
	flight[i1][i2] = cost;
      }
    }

    fscanf(in, "%d", &Q);
    for (j = 0; j < Q; j++) {
      fscanf(in, "%d", &stops);
      cost = search(stops);
      if (cost >= 0) {
	fprintf(out, "Total cost of flight(s) is $%d\n", cost);
      } else {
	fprintf(out, "No satisfactory flights\n");
      }
    }
  }
  return 0;
}
