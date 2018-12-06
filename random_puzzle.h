#ifndef GRID_H
#define GRID_H

#define N 9   // row and col
#define SRN 3 // square and row
#define K 20  //missing digits

int mat[N][N];

// retourne faux si 3x3 block contient un nombre
bool unUsedInBox(int rowStart, int colStart, int num)
{
  for (int i = 0; i < SRN; i++)
    for (int j = 0; j < SRN; j++)
      if (mat[rowStart + i][colStart + j] == num)
        return false;

  return true;
}

//random
int randomGenerator(int num)
{
  return (int)(rand() % num) + 1;
}

// check dans la ligne une occurence
bool unUsedInRow(int i, int num)
{
  for (int j = 0; j < N; j++)
    if (mat[i][j] == num)
      return false;
  return true;
}

// check dans la colonne une occurence
bool unUsedInCol(int j, int num)
{
  for (int i = 0; i < N; i++)
    if (mat[i][j] == num)
      return false;
  return true;
}

// check si on peut insérer dans une case
bool CheckIfSafe(int i, int j, int num)
{
  return (unUsedInRow(i, num) &&
          unUsedInCol(j, num) &&
          unUsedInBox(i - i % SRN, j - j % SRN, num));
}

// on remplit 3x3
void fillBox(int row, int col)
{
  int num;
  for (int i = 0; i < SRN; i++)
  {
    for (int j = 0; j < SRN; j++)
    {
      do
      {
        num = randomGenerator(N);
      } while (!unUsedInBox(row, col, num));

      mat[row + i][col + j] = num;
    }
  }
}

// on remplit la diagonal
void fillDiagonal()
{
  for (int i = 0; i < N; i = i + SRN)
    fillBox(i, i); // for diagonal box, start coordinates->i==j
}

// recursive function pour remplir le reste
bool fillRemaining(int i, int j)
{
  if (j >= N && i < N - 1)
  {
    i = i + 1;
    j = 0;
  }
  if (i >= N && j >= N)
  {
    return true;
  }

  if (i < SRN)
  {
    if (j < SRN)
      j = SRN;
  }
  else if (i < N - SRN)
  {
    if (j == (int)(i / SRN) * SRN)
      j = j + SRN;
  }
  else
  {
    if (j == N - SRN)
    {
      i = i + 1;
      j = 0;
      if (i >= N)
        return true;
    }
  }

  for (int num = 1; num <= N; num++)
  {
    if (CheckIfSafe(i, j, num))
    {
      mat[i][j] = num;
      if (fillRemaining(i, j + 1))
        return true;

      mat[i][j] = 0;
    }
  }
  return false;
}

// shuffle
void removeKDigits()
{
  int count = K;
  while (count != 0)
  {
    int cellId = randomGenerator(N * N);

    int i = (cellId / N);
    int j = cellId % 9;
    if (j != 0)
      j = j - 1;

    if (mat[i][j] != 0)
    {
      count--;
      mat[i][j] = 0;
    }
  }
}
// sudoku generate
void fillValues()
{
  // remplit la diagonal 3x3
  fillDiagonal();

  // on remplit le reste avec une function recursive
  fillRemaining(0, SRN);

  // shuffle
  removeKDigits();
}

void printSudoku()
{
  FILE *f = fopen("sudoku_grid/random.txt", "w");
  if (f == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      fprintf(f, "%d", mat[i][j]);
      fprintf(f, " ");
    }
    fprintf(f, "\n");
  }
  fprintf(f, "\n");
  printf("Puzzle successfully writed in random.txt !\n");
}

int startGenerate()
{
  srand(time(NULL));
  fillValues();
  printSudoku();
}

#endif