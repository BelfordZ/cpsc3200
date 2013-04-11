#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
  char line[1024];
  double width, height, ratio, nom_d;
  double d, circ;
  double pi = acos(-1);
  FILE *in, *out;

  if (!(in = fopen("tire.in", "r")) || !(out = fopen("tire.out", "w"))) {
    fprintf(stderr, "Cannot open input/output\n");
    return 1;
  }

  while (fgets(line, 1024, in)) {
    line[strlen(line)-1] = '\0';
    if (sscanf(line, "%*s %lf / %lf %*s %lf", &width, &ratio, &nom_d) != 3) {
      sscanf(line, "%*s %lf / %lf %*s %*s %lf", &width, &ratio, &nom_d);
    }

    height = ratio * width / 100;
    d = 2*height + nom_d*25.4;
    circ = d * pi/10;
    fprintf(out, "%s: %.0f\n", line, circ);
  }
  return 0;
}
