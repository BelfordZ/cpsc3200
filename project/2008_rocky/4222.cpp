/* Howard Cheng */

#include <stdio.h>
#include <string.h>

#define MAX_STEP 1000
#define MAX_WORD 100

int rule1(char dance[MAX_STEP][MAX_WORD+1], int n)
{
  int i;
  int ret = 0;
  for (i = 0; i < n; i++) {
    if (strcmp(dance[i], "dip")) continue;
    if (!((i >= 2 && !strcmp(dance[i-2], "jiggle")) ||
	  (i >= 1 && !strcmp(dance[i-1], "jiggle")) ||
	  (i < n-1 && !strcmp(dance[i+1], "twirl")))) {
      strcpy(dance[i], "DIP");
      ret = 1;
    }
  }
  return ret;
}

int rule2(char dance[MAX_STEP][MAX_WORD+1], int n)
{
  return !(n >= 3 && !strcmp(dance[n-3], "clap") && 
	   !strcmp(dance[n-2], "stomp") &&
	   !strcmp(dance[n-1], "clap"));
}

int rule3(char dance[MAX_STEP][MAX_WORD+1], int n)
{
  char twirl = 0, hop = 0;
  int i;

  for (i = 0; i < n; i++) {
    if (!strcmp(dance[i], "twirl")) twirl = 1;
    if (!strcmp(dance[i], "hop")) hop = 1;
  }
  return twirl && !hop;
}

int rule4(char dance[MAX_STEP][MAX_WORD+1], int n)
{
  return n >= 1 && !strcmp(dance[0], "jiggle");
}

int rule5(char dance[MAX_STEP][MAX_WORD+1], int n)
{
  int i;
  for (i = 0; i < n; i++) {
    if (!strcmp(dance[i], "dip")) {
      return 0;
    }
  }
  return 1;
}

int main(void)
{
  char dance[MAX_STEP][MAX_WORD+1];
  char line[MAX_STEP*(MAX_WORD+1)+2];
  char *p;
  char rule[6];
  int n, i;
  int errors;

  FILE *in, *out;

  in = fopen("dance.in", "r");
  out = fopen("dance.out", "w");

  while (fgets(line, MAX_STEP*(MAX_WORD+1)+2, in)) {
    n = 0;
    for (p = line; (p = strtok(p, " \n")); p = NULL) {
      strcpy(dance[n++], p);
    }
    errors = 0;
    errors += rule[2] = rule2(dance, n);
    errors += rule[3] = rule3(dance, n);
    errors += rule[4] = rule4(dance, n);
    errors += rule[5] = rule5(dance, n);
    errors += rule[1] = rule1(dance, n);

    fprintf(out, "form ");
    if (errors) {
      fprintf(out, "error%s ", (errors > 1 ? "s" : ""));
      for (i = 1; i <= 5; i++) {
	if (rule[i]) {
	  fprintf(out, "%d", i);
	  if (errors > 2) {
	    fprintf(out, ", ");
	  }
	  if (errors == 2) {
	    fprintf(out, " and ");
	  }
	  errors--;
	}
      }
      fprintf(out, ":");
    } else {
      fprintf(out, "ok:");
    }

    for (i = 0; i < n; i++) {
      fprintf(out, " %s", dance[i]);
    }
    fprintf(out, "\n");
  }

  return 0;
}
