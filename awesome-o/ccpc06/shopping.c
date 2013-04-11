#include <stdio.h>
#include <math.h>

FILE *in, *out;

int M, N, P;

int G[51][51];
int store[51];
int dvd[51];

int permute(int *perm, int n, int index)
{
  int i, t, best;

  if (index >= n) {
    best = -G[0][perm[0]] - G[perm[n-1]][0];
    for (i = 1; i < n; i++) {
      best -= G[perm[i-1]][perm[i]];
    }
    for (i = 0; i < n; i++) {
      best += store[perm[i]];
    }
    return best;
  }

  best = -1;
  for (i = index; i < n; i++) {
    t = perm[index];
    perm[index] = perm[i];
    perm[i] = t;
    t = permute(perm, n, index+1);
    if (t > best) {
      best = t;
    }
    t = perm[index];
    perm[index] = perm[i];
    perm[i] = t;
  }

  return best;
}

int gen_subset(int *subset, int subsize, int dvd_index)
{
  int t1, t2;

  if (dvd_index >= P) {
    return (subsize > 0) ? permute(subset, subsize, 0) : 0;
  }

  t1 = gen_subset(subset, subsize, dvd_index+1);
  subset[subsize] = dvd[dvd_index];
  t2 = gen_subset(subset, subsize+1, dvd_index+1);
  return (t2 > t1) ? t2 : t1;
}

void solve_case(void)
{
  int i, j, k, temp;
  double t;
  int best;
  int subset[51];

  fscanf(in, "%d %d", &N, &M);

  for (i = 0; i <= N; i++) {
    for (j = 0; j <= N; j++) {
      G[i][j] = -1;
    }
  }

  for (k = 0; k < M; k++) {
    fscanf(in, "%d %d %lf", &i, &j, &t);
    temp = (int)floor(t*100+0.5);
    if (G[i][j] == -1 || temp < G[i][j]) {
      G[i][j] = G[j][i] = temp;
    }
  }

  fscanf(in, "%d", &P);
  for (k = 0; k < P; k++) {
    fscanf(in, "%d %lf", &i, &t);
    dvd[k] = i;
    store[i] = (int)floor(t*100+0.5);
  }
  
  for (k = 0; k <= N; k++) {
    for (i = 0; i <= N; i++) {
      for (j = 0; j <= N; j++) {
	if (G[i][k] != -1 && G[k][j] != -1) {
	  temp = G[i][k] + G[k][j];
	  if (G[i][j] == -1 || temp < G[i][j]) {
	    G[i][j] = temp;
	  }
	}
      }
    }
  }

  best = gen_subset(subset, 0, 0);
  if (best > 0) {
    fprintf(out, "Daniel can save $%.2f\n", best/100.0);
  } else {
    fprintf(out, "Don't leave the house\n");
  }
}

int main(void)
{
  int N;

  in = fopen("shopping.in", "r");
  out = fopen("shopping.out", "w");
  
  fscanf(in, "%d", &N);
  while (N-- > 0) {
    solve_case();
  }

  return 0;
}
