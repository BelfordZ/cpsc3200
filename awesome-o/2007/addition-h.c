#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_N 15
/* length of the string representation of each integer */
int len[MAX_N+1];

void compute_len(void)
{
  int n, i;

  len[0] = 2;
  for (n = 1; n <= MAX_N; n++) {
    len[n] = 2 + (n-1);   /* outside brackets and commas */
    for (i = 0; i < n; i++) {
      len[n] += len[i];
    }
  }
}

int read_int(FILE *in)
{
  int c, i;
  int l = 0;

  while ((c = fgetc(in)) != EOF && c != '\n') {
    assert(c == '{' || c == '}' || c == ',');
    l++;
  }
  for (i = 0; i <= MAX_N; i++) {
    if (len[i] == l) {
      return i;
    }
  }
  assert(0);
  return -1;
}

void write_int(FILE *out, int n)
{
  int i;

  fprintf(out, "{");
  for (i = 0; i < n; i++) {
    if (i) {
      fprintf(out, ",");
    }
    write_int(out, i);
  }
  fprintf(out, "}");
}

int main(void)
{
  FILE *in, *out;
  int cases;
  int a, b;

  if (!(in = fopen("addition.in", "r"))) {
    fprintf(stderr, "Cannot open input file\n");
    exit(1);
  }
  if (!(out = fopen("addition.out", "w"))) {
    fprintf(stderr, "Cannot open output file\n");
    exit(1);
  }

  compute_len();

  fscanf(in, "%d\n", &cases);
  while (cases-- > 0) {
    a = read_int(in);
    b = read_int(in);
    write_int(out, a+b);
    fprintf(out, "\n");
  }
  
  fclose(in);
  fclose(out);

  return 0;
}
