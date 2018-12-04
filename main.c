#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>


// constante ligne colonne, valeur et taille du carré sudoku
#define rows 9
#define cols 9
#define values 9
#define box_width 3


//grille
int grid[rows][cols];


//chargmement du fichier et du contenu
int sudokuFile (const char *path) {
	FILE *file = fopen(path, "r");
	
	if (!file){
		return false;
	}

	// push du tableau sudoku dans le grid
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			fscanf(file, "%d", &grid[row][col]);
		}
	}
	
	fclose(file);
	
	return true;
}

int valid (int row, int col, int val) {
	for (int n = 0; n < rows; n++) {
		if (grid[n][col] == val || grid[row][n] == val){
            return false;
        }
	}
	int tmp_row = (row / box_width) * box_width;
	int tmp_col = (col / box_width) * box_width;
	
	for (int r = tmp_row; r < tmp_row + box_width; r++) {
		for (int c = tmp_col; c < tmp_col + box_width; c++) {
			if (grid[r][c] == val){
                return false;
            }
		}
	}
	
	return true;
}

int solve (int row, int col) {
	if (row == rows){
		return true;
	}
	
	if (grid[row][col] != 0) {
		if (col == 8){
			return solve(row + 1, 0);
		}
		return solve(row, col + 1);
	}
	
	for (int val = 1; val <= values; val++) {
		if (valid(row, col, val)) {
			grid[row][col] = val;
			
			if (col == 8) {
				if (solve(row + 1, 0)){
					return true;
				}
			}
			else {
				if (solve(row, col + 1)){
					return true;
				}
			}
		}
	}
	
	grid[row][col] = 0;
	
	return false;
}

int main (int argc, const char * argv[]) {
    float temps;
    clock_t t1, t2;
 
    t1 = clock();
	if (argc != 2) {
		printf("Usage: sudoku /path/to/sudoku.txt\n");
		
		return EXIT_SUCCESS;
	}
	
	char realPath[PATH_MAX + 1];
	char *res = realpath(argv[1], realPath);
	
	if (!res) {
		printf("Invalid sudoku path!\n");
		
		return EXIT_FAILURE;
	}
	
	if (!sudokuFile(realPath)) {
		printf("Couldn't load the sudoku!\n");
		
		return EXIT_FAILURE;
	}else{
		if(solve(0,0)){
			for (int row = 0; row < rows; row++) {
				for (int col = 0; col < cols; col++) {
					printf("%d ", grid[row][col]);
				}
				
				printf("\n");
			}
		}else{
			printf("I have no solution !");
		}
    }

    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;

	printf("time = %f\n", temps);
	
	return EXIT_SUCCESS;
}