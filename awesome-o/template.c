/* standard includes section */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

/* change to reflect root name of the problem */
#define INPUT "X.in"
#define OUTPUT "X.out"

FILE *in=0;
FILE *out=0;

void solve_problem();

int main(void)
{
    in = fopen(INPUT, "r");
    out = fopen(OUTPUT, "w");
    assert(in && out);

    solve_problem();

    fclose(in);
    fclose(out);

    return 0;
}


/* this is the real work: the input and output files are opened, and
   you must solve the problem.  */

void solve_problem()
{

}
