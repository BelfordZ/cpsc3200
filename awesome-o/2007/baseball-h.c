#include <stdio.h>
#include <assert.h>

FILE *in, *out;

#define MAX_TEAMNAME 15
#define MAX_PLAYERNAME 15

typedef struct {
  char team[MAX_TEAMNAME+1];
  char name[9][MAX_PLAYERNAME+1];
  double hit[9], sac[9];
  int curr;
  int runs, hits;
} Team;

Team home, visitor;

int seed;

void mysrand(int s)
{
  seed = s;
}

int myrand(void)
{
/*
  seed = seed * 1103515245 + 12345;
  return seed/65536 % 32768;
*/
  seed = (seed * 25173 + 13849) % 65536;
  return seed;
}

void read_team(Team *team)
{
  int i;

  fscanf(in, "%s", team->team);
  for (i = 0; i < 9; i++) {
    fscanf(in, "%s %lf %lf", team->name[i], (team->hit)+i, (team->sac)+i);
  }
  team->curr = team->hits = team->runs = 0;
}

int success(double rate)
{
  double r = myrand();
  r = r / 65536.0;
  return r <= rate;
}

void process_half(Team *team, int *runs, int *hits, int *nruns, int *nhits,
		  int offset)
{
  int base[5];
  int out = 0;
  int i;

  /* all bases empty */
  base[1] = base[2] = base[3] = base[4] = -1;
  while (out < 3) {
    if ((base[2] >= 0 && out == 0) || (base[3] >= 0 && out <= 1)) {
      /* sacrifice */
      if (success(team->sac[team->curr])) {
	for (i = 4; i >= 2; i--) {
	  base[i] = base[i-1];
	}
	base[1] = -1;
      }
      out++;
    } else {
      /* normal hit */
      if (success(team->hit[team->curr])) {
	for (i = 4; i >= 2; i--) {
	  base[i] = base[i-1];
	}
	base[1] = team->curr + offset;
	hits[(*nhits)++] = team->curr + offset;
	team->hits++;
      } else {
	out++;
      }
    }
    if (++team->curr == 9) {
      team->curr = 0;
    }
    if (out < 3 && base[4] >= 0) {
      runs[(*nruns)++] = base[4];
      base[4] = -1;
      team->runs++;
    }
  }
}

void process_inning(int inning)
{
  int runs[1000], hits[1000];
  int nruns, nhits;
  int i;

  nruns = nhits = 0;

  fprintf(out, "Inning %d:\n", inning);

  process_half(&visitor, runs, hits, &nruns, &nhits, 0);
  if (inning != 9 || visitor.runs >= home.runs) {
    process_half(&home, runs, hits, &nruns, &nhits, 100);
  }
  assert(nruns < 1000 && nhits < 1000);

  fprintf(out, "Hits:\n");
  if (nhits > 0) {
    for (i = 0; i < nhits; i++) {
      if (hits[i] < 100) {
	fprintf(out, "  %15s %15s\n", visitor.name[hits[i]], visitor.team);
      } else {
	hits[i] -= 100;
	fprintf(out, "  %15s %15s\n", home.name[hits[i]], home.team);
      }
    }
  } else {
    fprintf(out, "  none\n");
  }
  fprintf(out, "\nRuns:\n");
  if (nruns > 0) {
    for (i = 0; i < nruns; i++) {
      if (runs[i] < 100) {
	fprintf(out, "  %15s %15s\n", visitor.name[runs[i]], visitor.team);
      } else {
	runs[i] -= 100;
	fprintf(out, "  %15s %15s\n", home.name[runs[i]], home.team);
      }
    }
  } else {
    fprintf(out, "  none\n");
  }
  fprintf(out, "\n");
}

int main(void)
{
  int games;
  int i, j;
  int inning;

  in = fopen("baseball.in", "r");
  out = fopen("baseball.out", "w");
  assert(in && out);

  fscanf(in, "%d\n", &games);
  for (i = 1; i <= games; i++) {
    mysrand(1);
    read_team(&visitor);
    read_team(&home);

    if (i > 1) {
      for (j = 0; j < 60; j++) {
	fputc('=', out);
      }
      fputc('\n', out);
    }
    fprintf(out, "Game %d: %s vs. %s\n\n", i, visitor.team, home.team);
    
    for (inning = 1; inning <= 9; inning++) {
      process_inning(inning);
    }
    while (visitor.runs == home.runs) {
      assert(inning <= 200);
      process_inning(inning++);
    }

    fprintf(out, "End of Game:\n");
    fprintf(out, "  %15s %d runs, %d hits\n", visitor.team, visitor.runs,
	    visitor.hits);
    fprintf(out, "  %15s %d runs, %d hits\n", home.team, home.runs, home.hits);
  }

  return 0;
}
