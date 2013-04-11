#include <stdio.h>

int binom[13][13];
int derange[13] = {1, 0, 1};

int main(void)
{
  FILE *in, *out;
  int n, k, i, ans;

  in = fopen("invitations.in", "r");
  out = fopen("invitations.out", "w");
  
  for (n = 0; n <= 12; n++) {
    for (k = 0; k <= 12; k++) {
      if (k == 0 || n == k) {
	binom[n][k] = 1;
      } else {
	binom[n][k] = binom[n-1][k] + binom[n-1][k-1];
      }
    }
  }

  for (n = 3; n <= 12; n++) {
    derange[n] = (n-1)*(derange[n-1] + derange[n-2]);
  }

  while (fscanf(in, "%d %d", &n, &k) == 2) {
    ans = 0;
    for (i = 0; i <= k; i++) {
      ans += binom[n][i] * derange[n-i];
    }
    fprintf(out, "%d\n", ans);

  }


  return 0;
}
