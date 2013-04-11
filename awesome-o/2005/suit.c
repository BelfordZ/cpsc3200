/*
 * Solution to Suit Distribution
 *
 * Howard Cheng
 *
 * The idea is that we only have to consider the distribution of one
 * opponent because once 3 hands are known the 4th one is fixed.
 * There are binom(26,13) ways to distribute the remaining 26 cards to
 * the opponent.  The number of ways for the opponent to get "a" cards
 * and his partner "b" cards in a suit is:
 *
 *   binom(a+b, a) * binom(26-(a+b), 13-a)
 *
 * 1st factor: number of ways to take the "a" cards in the suit
 * 2nd factor: number of ways to choose the remaining cards in the
 *             other suits
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 26
int binom[MAX_N+1][MAX_N+1];

/* precompute all the binomial coefficients */
void compute_binom(void);

int main(void)
{
  int a, b;
  double p;
  FILE *in, *out;

  if (!(in = fopen("suit.in", "r")) || !(out = fopen("suit.out", "w"))) {
    fprintf(stderr, "Cannot open input/output files\n");
    exit(1);
  }

  compute_binom();
  while (fscanf(in, "%d %d", &a, &b) == 2 && !(a == -1 && b == -1)) {
    p = (double)(binom[a+b][a] * binom[26-(a+b)][13-a])/binom[26][13];
    if (a != b) {
      /* account for symmetry */
      p *= 2;
    }
    fprintf(out, "%d-%d split: %.8f\n", a, b, p);
  }

  return 0;
}

/* precompute all the binomial coefficients */
void compute_binom(void)
{
  int n, k;

  for (n = 0; n <= MAX_N; n++) {
    binom[n][0] = binom[n][n] = 1;
    for (k = 1; k < n; k++) {
      binom[n][k] = binom[n-1][k] + binom[n-1][k-1];
    }
  }
}
