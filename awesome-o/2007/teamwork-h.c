#include <stdio.h>
#include <assert.h>

#define MAX_N 13
#define MAX_LEN 25

FILE *in, *out;

int N;
int sticks[MAX_LEN+1];

int read_case(void)
{
  int i, x;

  fscanf(in, "%d", &N);
  if (!N) {
    return 0;
  }
  for (i = 0; i <= MAX_LEN; i++) {
    sticks[i] = 0;
  }
  for (i = 0; i < N; i++) {
    fscanf(in, "%d", &x);
    sticks[x]++;
  }

  return 1;
}

int solve(int stick_len, char *connect, int stick, int currlen, int *first3)
{
  int l;

  if (stick_len == currlen) {
    currlen = 0;
    stick++;
    if (stick == 3) {
      return 1;
    }
  }
  /* we already fixed the first one */
  if (!currlen) {
    return solve(stick_len, connect, stick, first3[stick], first3);
  }

  for (l = 1; l <= MAX_LEN && l + currlen <= stick_len; l++) {
    if (!sticks[l]) continue;
    if (l + currlen < stick_len && connect[l+currlen]) continue;
    sticks[l]--;
    connect[l+currlen] = 1;
    if (solve(stick_len, connect, stick, l+currlen, first3)) {
      return 1;
    }
    connect[l+currlen] = 0;
    sticks[l]++;
  }
  return 0;
}

int solve_case(void)
{
  int l, j;
  int i1, i2, i3;
  int sum = 0;
  char connect[MAX_N*MAX_LEN+1];
  int first3[3];

  for (l = 1; l <= MAX_LEN; l++) {
    sum += sticks[l]*l;
  }

  for (j = 0; j <= sum/3; j++) {
    connect[j] = 0;
  }
  
  for (l = sum/3; l >= 1; l--) {

    /* fix the first three sticks in each final stick */
    for (i1 = 1; i1 <= MAX_LEN && i1 < l; i1++) {
      if (!sticks[i1]) continue;
      sticks[i1]--;
      first3[0] = i1;
      connect[i1] = 1;
      for (i2 = i1+1; i2 <= MAX_LEN && i2 < l; i2++) {
	if (!sticks[i2]) continue;
	sticks[i2]--;
	first3[1] = i2;
	connect[i2] = 1;
	for (i3 = i2+1; i3 <= MAX_LEN && i3 < l; i3++) {
	  if (!sticks[i3]) continue;
	  sticks[i3]--;
	  first3[2] = i3;
	  connect[i3] = 1;
	  if (solve(l, connect, 0, 0, first3)) {
	    return l;
	  }
	  sticks[i3]++;
	  connect[i3] = 0;
	}
	sticks[i2]++;
	connect[i2] = 0;
      }
      sticks[i1]++;
      connect[i1] = 0;
      }
  }
  return 0;
}

int main(void)
{
  int case_no = 1;

  in = fopen("teamwork.in", "r");
  out = fopen("teamwork.out", "w");
  assert(in && out);
  while (read_case()) {
    fprintf(out, "Case %d: %d\n", case_no++, solve_case());
  }
  return 0;
}
