#include <stdio.h>
#include <stdlib.h>

#define MAX_MN 256
#define MAX_S 4
#define MAX_B (2*MAX_S+1)

FILE *in, *out;
int M, N, S;

char A[MAX_MN][MAX_MN+1], B[MAX_B][MAX_B+1];

void print_image(char C[MAX_MN][MAX_MN+1])
{
  int i, j;

  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      fputc(C[i][j] ? '*' : '.', out);
    }
    fputc('\n', out);
  }
}

int read_case(void)
{
  int i, j;

  fscanf(in, "%d %d %d", &M, &N, &S);
  if (!M && !N && !S) {
    return 0;
  }

  for (i = 0; i < M; i++) {
    fscanf(in, "%s", A[i]);
    for (j = 0; j < N; j++) {
      A[i][j] = (A[i][j] == '*');
    }
  }
  for (i = 0; i < 2*S+1; i++) {
    fscanf(in, "%s", B[i]);
    for (j = 0; j < 2*S+1; j++) {
      B[i][j] = (B[i][j] == '*');
    }
  }

  return 1;
}

void dilation(char A[MAX_MN][MAX_MN+1], char B[MAX_B][MAX_B+1],
	      char C[MAX_MN][MAX_MN+1])
{
  int i, j, i2, j2, i3, j3;

  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      C[i][j] = 0;
    }
  }

  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      if (A[i][j]) {
	for (i2 = 0; i2 < 2*S+1; i2++) {
	  for (j2 = 0; j2 < 2*S+1; j2++) {
	    if (B[i2][j2]) {
	      i3 = i + i2 - S;
	      j3 = j + j2 - S;
	      if (0 <= i3 && i3 < M && 0 <= j3 && j3 < N) {
		C[i3][j3] = 1;
	      }
	    }
	  }
	}
      }
    }
  }
}

void erosion(char A[MAX_MN][MAX_MN+1], char B[MAX_B][MAX_B+1],
	     char C[MAX_MN][MAX_MN+1])
{
  int i, j, i2, j2, i3, j3;

  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      C[i][j] = 1;
    }
  }

  for (i3 = 0; i3 < M; i3++) {
    for (j3 = 0; j3 < N; j3++) {
      for (i2 = 0; C[i3][j3] && i2 < 2*S+1; i2++) {
	for (j2 = 0; C[i3][j3] && j2 < 2*S+1; j2++) {
	  if (B[i2][j2]) {
	    i = i3 + i2 - S;
	    j = j3 + j2 - S;
	    if (!(0 <= i && i < M && 0 <= j && j < N && A[i][j])) {
	      C[i3][j3] = 0;
	    }
	  }
	}
      }
    }
  }
}

void opening(char A[MAX_MN][MAX_MN+1], char B[MAX_B][MAX_B+1],
	     char C[MAX_MN][MAX_MN+1])
{
  char temp[MAX_MN][MAX_MN+1];
  
  erosion(A, B, temp);
  dilation(temp, B, C);
}

void closing(char A[MAX_MN][MAX_MN+1], char B[MAX_B][MAX_B+1],
	     char C[MAX_MN][MAX_MN+1])
{
  char temp[MAX_MN][MAX_MN+1];

  dilation(A, B, temp);
  erosion(temp, B, C);
}

void solve_case(void)
{
  char C[MAX_MN][MAX_MN+1];

  opening(A, B, C);
  print_image(C);
  fprintf(out, "\n");
  closing(A, B, C);
  print_image(C);
}

int main(void)
{
  int case_num = 0;
  int i;

  if (!(in = fopen("openclose.in", "r")) ||
      !(out = fopen("openclose.out", "w"))) {
    fprintf(stderr, "Cannot open input/output.\n");
    exit(1);
  }

  while (read_case()) {
    if (case_num++) {
      for (i = 0; i < 75; i++) {
	fputc('=', out);
      }
      fputc('\n', out);
    }
    fprintf(out, "Case %d\n\n", case_num);
    solve_case();
  }
  return 0;
}
