#include <stdio.h>
#include <ctype.h>

char *qwerty = "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?";

char *dvorak = "`123qjlmfp/[]456.orsuyb;=\\789aehtdck-0zx,inwvg'~!@#QJLMFP?{}$%^>ORSUYB:+|&*(AEHTDCK_)ZX<INWVG\"";

int main(void)
{
  FILE *in, *out;
  int c, i;

  in = fopen("typist.in", "r");
  out = fopen("typist.out", "w");

  while ((c = fgetc(in)) != EOF) {
    if (isspace(c)) {
      fputc(c, out);
    } else {
      for (i = 0; dvorak[i]; i++) {
	if (qwerty[i] == c) {
	  fputc(dvorak[i], out);
	  break;
	}
      }
    }

  }

  return 0;
}
