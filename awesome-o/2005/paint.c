#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TOL 0.00001
#define CUPS_PER_GALLON 16

int main(void)
{
  double B, W, C;
  double B1, W1, B2, W2, BC, WC;
  int i;

  FILE *in, *out;

  if (!(in = fopen("paint.in", "r"))) {
    fprintf(stderr, "Cannot open input\n");
    exit(1);
  }
  if (!(out = fopen("paint.out", "w"))) {
    fprintf(stderr, "Cannot open output\n");
    exit(1);
  }

  while (fscanf(in, "%lf %lf %lf", &B, &W, &C) == 3 && B && W && C) {
    i = 0;
    B *= CUPS_PER_GALLON;
    W *= CUPS_PER_GALLON;
    B1 = B;   W1 = 0;
    B2 = 0;   W2 = W;
    do {
      /* move from pail 1 to pail 2 */
      BC = C * B1/(B1+W1);
      WC = C * W1/(B1+W1);
      B1 -= BC;
      W1 -= WC;
      B2 += BC;
      W2 += WC;

      /* move from pail 2 to pail 1 */
      BC = C * B2/(B2+W2);
      WC = C * W2/(B2+W2);
      B2 -= BC;
      W2 -= WC;
      B1 += BC;
      W1 += WC;

      i++;

      /*
      fprintf(out, "%d: deviation: %10g %10g\n", i, fabs(B1/W1 - B/W), fabs(B2/W2 - B/W));
      fprintf(out, "B1: %.12f  W1: %.12f\n", B1, W1);
      fprintf(out, "B2: %.12f  W2: %.12f\n", B2, W2);
      */

    } while (fabs(B1/W1 - B/W) >= TOL || fabs(B2/W2 - B/W) >= TOL);
    fprintf(out, "%d\n", i);
  }
  return 0;
}
