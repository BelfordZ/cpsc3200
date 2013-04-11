#include <stdio.h>
#include <assert.h>

#define MAX_N 256

void invtransform(int *signal, int n)
{
  int temp[MAX_N];
  int i;

  for (i = 0; i < n/2; i++) {
    assert((signal[i] + signal[n/2+i]) % 2 == 0);
    assert((signal[i] - signal[n/2+i]) % 2 == 0);
    temp[2*i]   = (signal[i] + signal[n/2+i])/2;
    temp[2*i+1] = (signal[i] - signal[n/2+i])/2; 
  }
  for (i = 0; i < n; i++) {
    signal[i] = temp[i];
  }
}

void invpyramid(int *signal, int N)
{
  int n;
  for (n = 2; n <= N; n *= 2) {
    invtransform(signal, n);
  }
}

int main(void)
{
  int N;
  FILE *in, *out;
  int signal[MAX_N];
  int i;

  in = fopen("wavelet.in", "r");
  out = fopen("wavelet.out", "w");
  assert(in && out);

  while (fscanf(in, "%d", &N) == 1 && N > 0) {
    for (i = 0; i < N; i++) {
      fscanf(in, "%d", signal+i);
    }

    invpyramid(signal, N);
    
    for (i = 0; i < N; i++) {
      if (i) {
	fprintf(out, " ");
      }
      assert(0 <= signal[i] && signal[i] <= 255);
      fprintf(out, "%d", signal[i]);
    }
    fprintf(out, "\n");
  }

  return 0;
}
