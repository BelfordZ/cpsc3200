#include <stdio.h>
#include <assert.h>

FILE *in, *out;

int calc_height(int level, int *height1)
{
  int c, n, t;
  int height = 0;

  if (level > *height1) {
    *height1 = level;
  }

  for (n = 0; (c = fgetc(in)) == 'd'; n++) {
    if ((t = calc_height(level+1, height1) + n+1) > height) {
      height = t;
    }
  }
  assert(c == 'u' || c == '\n');

  return height;
}

int main(void)
{
  int c, height1, height2, num = 1;

  in = fopen("graft.in", "r");
  out = fopen("graft.out", "w");
  assert(in && out);

  while ((c = fgetc(in)) != '#') {
    ungetc(c, in);
    height1 = 0;
    height2 = calc_height(0, &height1);
    fprintf(out, "Tree %d: %d => %d\n", num++, height1, height2);
  }

  return 0;
}
