#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int best;

void search(int *digits, int start, int n)
{
  int i, t;
  if (start >= n) {
    int a, b;

    a = b = 0;
    for (i = 0; i < n/2; i++) {
      a = 10*a + digits[i];
    }
    for (i = n/2; i < n; i++) {
      b = 10*b + digits[i];
    }
    t = (a < b) ? b - a : a - b;
    if (t < best) {
      best = t;
    }
  } else {
    for (i = start; i < n; i++) {
      t = digits[i];
      digits[i] = digits[start];
      digits[start] = t;
      if ((digits[0] != 0 || n/2 == 1) && 
	  (digits[n/2] != 0 || n - n/2 == 1)) {
	search(digits, start+1, n);
      }
      t = digits[i];
      digits[i] = digits[start];
      digits[start] = t;
    }
  }
}

int main(void)
{
  int cases;
  char line[1024], *p;
  int n, digits[10];
  FILE *in, *out;

  if (!(in = fopen("mindiff.in", "r")) || !(out = fopen("mindiff.out", "w"))) {
    fprintf(stderr, "Cannot open input/output\n");
    exit(1);
  }

  fscanf(in, "%d\n", &cases);
  while (cases-- > 0) {
    fgets(line, 1024, in);
    n = 0;
    for (p = line; p = strtok(p, " \n"); p = NULL) {
      digits[n++] = atoi(p);
    }
    best = INT_MAX;
    search(digits, 0, n);
    fprintf(out, "%d\n", best);
  }
  fclose(out);
  return 0;
}
