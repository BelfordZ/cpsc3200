#include <stdio.h>
#include <ctype.h>
#include <math.h>

char *qwerty[2][4] = {
  { 
    "`1234567890-=",
    " qwertyuiop[]\\",
    " asdfghjkl;'",
    " zxcvbnm,./"
  },
  {
    "~!@#$%^&*()_+",
    " QWERTYUIOP{}|",
    " ASDFGHJKL:\"",
    " ZXCVBNM<>?"
  }
};

char *dvorak[2][4] = {
  {
    "`123qjlmfp/[]",
    " 456.orsuyb;=\\",
    " 789aehtdck-",
    " 0zx,inwvg'"
  },
  {
    "~!@#QJLMFP?{}",
    " $%^>ORSUYB:+|",
    " &*(AEHTDCK_",
    " )ZX<INWVG\""
  }
};

char *qwertyhome = "asdfjkl;";
char *qwerty2home = "fghj";
char *dvorakhome = "ehtd";

double d(char c, char *keyboard[2][4], char c2)
{
  int i, j, k;
  int row1, col1, row2, col2;

  row1 = -1;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 4; j++) {
      for (k = 0; keyboard[i][j][k]; k++) {
	if (keyboard[i][j][k] == c) {
	  row1 = j;
	  col1 = k;
	}
	if (keyboard[i][j][k] == c2) {
	  row2 = j;
	  col2 = k;
	}
      }
    }
  }

  return 2*sqrt((row1-row2)*(row1-row2) + (col1-col2)*(col1-col2));

}

double dist(char c, char *keyboard[2][4], char *home)
{
  double best = d(c, keyboard, *home++);
  double t;

  while (*home) {
    t = d(c, keyboard, *home++);
    if (t < best) {
      best = t;
    }
  }
  return best;
}

int main(void)
{
  FILE *in, *out;
  char line[1024];
  int i;
  double total1, total2, total3;

  in = fopen("keyboard.in", "r");
  out = fopen("keyboard.out", "w");
  
  while (fgets(line, 1024, in)) {
    total1 = total2 = total3 = 0.0;

    for (i = 0; line[i]; i++) {
      if (isspace(line[i])) continue;
      total1 += dist(line[i], qwerty, qwertyhome);
      total2 += dist(line[i], qwerty, qwerty2home);
      total3 += dist(line[i], dvorak, dvorakhome);
    }
    fprintf(out, "%.2f %.2f %.2f\n", total1, total2, total3);
  }


  return 0;
}
