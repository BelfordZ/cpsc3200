/*
 * To follow the bouncing beam, don't reflect the beam.  Rather, extend
 * the hallway and let the beam run straight.  The only tricky issue is
 * that the vertical position at the end depends on whether the number
 * of bounces is odd or even.
 *
 */

#include <math.h>
#include <stdio.h>

int main(void)
{
  double A, B, theta;
  double pi = acos(-1.0);
  double L, W;
  double h;
  int n, bounce;

  scanf("%d", &n);
  while (n-- > 0) {
    scanf("%lf %lf %lf", &L, &W, &theta);
    theta *= pi / 180.0;
    A = L / cos(theta);
    h = L * tan(theta);
    bounce = 0;
    while (h >= W) {
      h -= W;
      bounce = 1-bounce;
    }
    if (bounce) {
      h = W - h;
    }
    B = hypot(L, h);
    printf("%.3f\n", A/B);
    
  }
  return 0;
}
