#include <stdio.h>
#include <math.h>

double round_down(double x)
{
  if (x - 0.5 >= 0) {
    return x - 0.5;
  } else {
    return 0;
  }
}

double round_up(double x)
{
  return x + 0.5;
}

int main(void)
{
  int cal, fat, carb, prot;
  double lo;
  double hi;

  FILE *in = fopen("close.in", "r");
  FILE *out = fopen("close.out", "w");

  while (fscanf(in, "%d %d %d %d", &cal, &fat, &carb, &prot) == 4 &&
	 (cal || fat || carb || prot)) {
    lo = round_down(fat)*9 + 4*(round_down(carb) + round_down(prot));
    hi = round_up(fat)*9 + 4*(round_up(carb) + round_up(prot));

    /* now the calories are in [lo, hi) */
    
    lo = floor(lo+0.5);
    hi = floor(hi+0.5);
    if (lo <= cal && cal < hi) {
      fprintf(out, "yes\n");
    } else {
      fprintf(out, "no\n");
    }
  }

  return 0;
}
