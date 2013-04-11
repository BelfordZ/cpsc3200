#include <stdio.h>
#include <math.h>


typedef struct {
  double x, y;
} Point;

int isfit(double a, double b, double c, double r)
{
  double theta, alpha;
  double x1, y1, x2, y2, x3, y3;

  if (a >= b && a >= c && a != c) {
    return isfit(b, c, a, r);
  }
  if (b >= a && b >= c && b != c) {
    return isfit(a, c, b, r);
  }

  if (2*r < c) {
    return 0;
  }
  theta = acos(1 - c*c/(2*r*r));
  x1 = -r*sin(theta/2);
  y1 = -r*cos(theta/2);
  x2 = -x1;
  y2 = y1;

  alpha = acos((b*b - a*a - c*c)/(-2*a*c));
  x3 = x1 + a*cos(alpha);
  y3 = y1 + a*sin(alpha);

  if (x3*x3+y3*y3 <= r*r) {
    return 1;
  } else {
    return 0;
  }

}

int main(void)
{
  FILE *in, *out;
  int M, N, i, j;
  double a, b, c;
  Point p1, p2, p3, center;

  double holes[100];
  char fit[100];
  int fit_count;
  double r;
  double theta;

  in = fopen("pegs.in", "r");
  out = fopen("pegs.out", "w");
  

  fscanf(in, "%d", &M);
  for (i = 0; i < M; i++) {
    fscanf(in, "%lf", holes+i);
  }
  fscanf(in, "%d", &N);
  for (i = 0; i < N; i++) {
    fscanf(in, "%lf %lf %lf", &a, &b, &c);

    fit_count = 0;
    
    for (j = 0; j < M; j++) {
      fit_count += (fit[j] = isfit(a, b, c, holes[j]/2.0));
    }
    
    if (fit_count) {
      fprintf(out, "Peg %c will fit into hole(s):", 'A'+i);
      for (j = 0; j < M; j++) {
	if (fit[j]) {
	  fprintf(out, " %d", j+1);
	}
      }
      fprintf(out, "\n");
    } else {
      fprintf(out, "Peg %c will not fit into any holes\n", 'A'+i);
    }

  }

  return 0;
}
