#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define rows 9
#define cols 9
#define values 9
#define box_width 3

int grid[rows][cols];

int sudokuFile (const char *path) {
	FILE *file = fopen(path, "r");
	
	if (!file)
		return 0;
	
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			fscanf(file, "%d", &grid[row][col]);
		}
	}
	
	fclose(file);
	
	return 1;
}

int valid (int row, int col, int val) {

}

int solve (int row, int col) {

}

int main (int argc, const char * argv[]) {
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
	}
	
	return EXIT_SUCCESS;
}