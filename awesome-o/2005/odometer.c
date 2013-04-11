#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIGITS 9

/* skipped[i] = number of skipped numbers with i digits */
int skipped[MAX_DIGITS];

FILE *in, *out;

int main(void)
{
  char meter[MAX_DIGITS+1];
  int i, p, l, ans, t;

  if (!(in = fopen("odometer.in", "r"))) {
    fprintf(stderr, "Can't open input file\n");
    exit(-1);
  }
  if (!(out = fopen("odometer.out", "w"))) {
    fprintf(stderr, "Can't open output file\n");
    exit(-1);
  }

  skipped[0] = 0;
  p = 1;
  for (i = 1; i < MAX_DIGITS; i++) {
    skipped[i] = skipped[i-1]*9 + p;
    p *= 10;
  }

  while (fscanf(in, "%s", meter) == 1 && strcmp(meter, "0")) {
    l = strlen(meter);
    ans = atoi(meter);

    p = 1;
    for (i = 0; i < l-1; i++) {
      p *= 10;
    }

    for (i = 0; i < l; i++) {
      t = meter[i] - '0';
      if (t < 4) {
	ans -= t*skipped[l-i-1];
      } else {
	ans -= (t-1)*skipped[l-i-1] + p;
      }
      p /= 10;
    }
    fprintf(out, "%s: %d\n", meter, ans);
  }
  
  return 0;
}
