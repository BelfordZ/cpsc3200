#include <stdio.h>
#include <string.h>

FILE *in, *out;

int score[17] = {
  0, 0, 0, 1, 1, 2, 3, 5, 11, 11, 11, 11, 11, 11, 11, 11, 11
};

int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1};

int search(char grid[4][5], char visited[4][4], char *word, int i, int j)
{
  int k;

  if (!(*word))
    return 1;

  if (i < 0 || j < 0 || i >= 4 || j >= 4)
    return 0;

  if (grid[i][j] != *word || visited[i][j])
    return 0;

  visited[i][j] = 1;
  for (k = 0; k < 8; k++) {
    if (search(grid, visited, word+1, i+dx[k], j+dy[k])) {
      return 1;
    }
  }
  
  visited[i][j] = 0;
  
  return 0;
}

int find(char grid[4][5], char *word)
{
  char visited[4][4];
  int i, j;

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      visited[i][j] = 0;
    }
  }

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (search(grid, visited, word, i, j)) {
	return 1;
      }
    }
  }

  return 0;
}

void solve_case(int game)
{
  char grid[4][5];
  char word[17];
  int i, M, total = 0;

  for (i = 0; i < 4; i++) {
    fscanf(in, "%s", grid[i]);
  }
  fscanf(in, "%d", &M);
  while (M-- > 0) {
    fscanf(in, "%s", word);
    if (find(grid, word)) {
      total += score[strlen(word)];
    }
  }

  fprintf(out, "Score for Boggle game #%d: %d\n", game, total);
}

int main(void)
{
  int N, i;

  in = fopen("boggle.in", "r");
  out = fopen("boggle.out", "w");
  
  fscanf(in, "%d", &N);
  for (i = 0; i < N; i++) {
    solve_case(i+1);
  }

  return 0;
}
