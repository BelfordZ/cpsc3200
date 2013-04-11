#include <stdio.h>
#include <assert.h>

#define MAX_M 100
#define MAX_N 26

int m, n;
char avail[MAX_M][MAX_N];
int start, end;
FILE *in, *out;

int read_case(void)
{
  int i, j;
  char line[MAX_N+1];

  fscanf(in, "%d %d", &m, &n);
  if (!m && !n) return 0;
  for (i = 0; i < m; i++) {
    fscanf(in, "%s", line);
    for (j = 0; j < n; j++) {
      avail[i][j] = (line[j] == 'O');
    }
  }

  fscanf(in, "%d %d", &start, &end);
  start--;
  end -= 2;    /* end is the last night, not checkout date */
  return 1;
}

void solve_case(void)
{
  int best[MAX_M][MAX_N];
  int succ[MAX_M][MAX_N];
  int i, j, k, temp, best_start, prev_room, start_day, num;

  /* start at the end */
  for (j = 0; j < n; j++) {
    best[end][j] = (avail[end][j]) ? 0 : -1;
    succ[end][j] = -1;
  }

  /* now go backwards */
  for (i = end-1; i >= start; i--) {
    for (j = 0; j < n; j++) {
      best[i][j] = succ[i][j] = -1;
      if (!avail[i][j]) continue;
      for (k = 0; k < n; k++) {
	if (best[i+1][k] < 0) continue;
	temp = best[i+1][k] + (j != k);
	if (best[i][j] == -1 || temp < best[i][j]) {
	  best[i][j] = temp;
	  succ[i][j] = k;
	}
      }
    }
  }

  /* now print the solution */
  best_start = num = -1;
  for (j = 0; j < n; j++) {
    if (best[start][j] < 0) continue;
    if (best_start == -1 || best[start][j] < num) {
      best_start = j;
      num = best[start][j];
    }
  }
  if (best_start < 0) {
    fprintf(out, "Not available\n");
  } else {
    prev_room = best_start;
    start_day = start;
    for (i = start; i <= end; i++) {
      best_start = succ[i][best_start];
      if (prev_room != best_start) {
	fprintf(out, "%c: %d-%d\n", (char)(prev_room+'A'), start_day+1, i+1+1);
	start_day = i+1;
	prev_room = best_start;
      }
    }
  }
}

int main(void)
{
  int case_no = 1;

  in = fopen("vacation.in", "r");
  out = fopen("vacation.out", "w");
  assert(in && out);

  while (read_case()) {
    if (case_no > 1) {
      fprintf(out, "\n");
    }
    fprintf(out, "Case %d:\n\n", case_no++);
    solve_case();
  }
  return 0;
}

