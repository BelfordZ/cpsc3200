/* Howard Cheng */

#include <stdio.h>

#define MAX_N 1000
/* i = how many depots */
/* j = how many attacks left */
int best[MAX_N+1][MAX_N+1];

/* val[i][j] = value for the chunk from i to j (inclusive) */
int val[MAX_N+1][MAX_N+1];

#ifndef SLOWER
void compute(int n, int m)
{
  int i;
  int temp;

  if (best[n][m] >= 0) {
    return;
  }
  if (!m) {
    best[n][m] = val[0][n-1];
    return;
  }
  if (n == m+1) {
    best[n][m] = 0;
    return;
  }

  /* figure out the last point to bomb (just after railroad i) */
  compute(n-1, m-1);
  best[n][m] = best[n-1][m-1] + val[n-1][n-1];
  
  for (i = n-3; i >= m-1; i--) {
    if (val[i+1][n-1] >= best[n][m]) {
      break;
    }
    compute(i+1, m-1);
    temp = best[i+1][m-1] + val[i+1][n-1];
    if (temp < best[n][m]) {
      best[n][m] = temp;
    }
  }
}

#else

/* this seems to be a slower version */
void compute(int n, int m)
{
  int i, j, k, temp;

  for (i = 1; i <= n; i++) {
    best[i][0] = val[0][i-1];
  }
  for (j = 1; j <= m; j++) {
    for (i = j+1; i <= n; i++) {
      best[i][j] = best[j][j-1] + val[j][i-1];
      for (k = j; k < i-1 && val[k+1][i-1] < best[i][j]; k++) {
	temp = best[k+1][j-1] + val[k+1][i-1];
	if (temp < best[i][j]) {
	  best[i][j] = temp;
	}
      }
    }
  }
}

#endif

void compute_val(int *A, int n)
{
  int i, j;
  int sum;

  for (i = 0; i < n; i++) {
    sum = A[i];
    for (j = i+1; j < n; j++) {
      val[i][j] = val[i][j-1]+sum*A[j];
	sum += A[j];
    }
  }
}

int main(void)
{
  int m, n;
  int A[MAX_N];
  int i, j;
  FILE *in, *out;

  in = fopen("lawrence.in", "r");
  out = fopen("lawrence.out", "w");

  while (fscanf(in, "%d %d", &n, &m) == 2 && (n || m)) {
    for (i = 0; i < n; i++) {
      fscanf(in, "%d", A+i);
    }

    for (i = 0; i <= n; i++) {
      for (j = 0; j <= m; j++) {
	best[i][j] = -1;
      }
    }

    compute_val(A, n);
    compute(n, m);

    fprintf(out, "%d\n", best[n][m]);
  }
  return 0;
}
