#include <stdio.h>
#include <assert.h>

#define MAX_LEN 1000

int main(void)
{
  char line[MAX_LEN+1];
  int cases;
  int i, j;
  FILE *in, *out;

  in = fopen("lookandsay.in", "r");
  out = fopen("lookandsay.out", "w");
  assert(in && out);

  fscanf(in, "%d", &cases);
  while (cases-- > 0) {
    fscanf(in, "%s", line);

    j = 0;
    for (i = 0; line[i]; i += j) {
      for (j = 0; line[i+j] == line[i]; j++)
	;
      fprintf(out, "%d%c", j, line[i]);
    }
    fprintf(out, "\n");
  }

  fclose(in);
  fclose(out);
  return 0;
}
