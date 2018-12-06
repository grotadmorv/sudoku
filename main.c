#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "random_puzzle.h"


// constante ligne colonne, valeur et taille du carré sudoku
#define ROWS 9
#define COLS 9
#define VALUES 9
#define BOX_WIDTH 3


// des couleurs pour que ça soit joli
#define MAGENTA   "\x1B[35m"
#define YELLOW   "\x1B[33m"
#define RESET "\x1B[0m"
#define CYAN   "\x1B[36m"



//grille
int grid[ROWS][COLS];


//chargement du fichier et du contenu
int sudokuFile (const char *path) {
	FILE *file = fopen(path, "r");
	
	if (!file){
		return false;
	}

	// push du tableau sudoku dans le grid
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			fscanf(file, "%d", &grid[row][col]);
		}
	}
	
	fclose(file);
	
	return true;
}


// valid function
int valid (int row, int col, int val) {

	// parcours des lignes
	for (int n = 0; n < ROWS; n++) {
		// si ça n ligne de la colonne ou n colonne de la ligne est egal à la valeur d'entrée, on renvoit faux 
		// --> solve passera à la suite
		if (grid[n][col] == val || grid[row][n] == val){
            return false;
        }
	}

	// modulo(reste) des lignes et colonnes

	int tmp_row = (row / BOX_WIDTH) * BOX_WIDTH;
	int tmp_col = (col / BOX_WIDTH) * BOX_WIDTH;
	

	// on parcours tout
	for (int r = tmp_row; r < tmp_row + BOX_WIDTH; r++) {
		for (int c = tmp_col; c < tmp_col + BOX_WIDTH; c++) {
			// si la case est egale à la valeur, on renvoit faux, ça passera à la suivante
			if (grid[r][c] == val){
                return false;
            }
		}
	}
	
	// sinon c'est ok :D
	return true;
}

// solve function

int solve (int row, int col) {
	//test de fin de la grille
	if (row == ROWS){
		return true;
	}
	//test si la case est =/= de 0
	if (grid[row][col] != 0) {
		//test si c'est la derniere colonne
		if (col == 8){
			//rapelle la fonction en passant la ligne et en se positionnant colonne 0
			return solve(row + 1, 0);
		}
		//rapelle la fonction pour passer la prochaine colonne
		return solve(row, col + 1);
	}

	//remplir les valeurs
	for (int val = 1; val <= VALUES; val++) {
		// test avec la fonction valide
		if (valid(row, col, val)) {
			grid[row][col] = val;
			
			if (col == 8) {
				//rappelle la fonction en passant la ligne et en se positionnant colonne 0
				if (solve(row + 1, 0)){
					return true;
				}
			}
			else {
				//rappelle la fonction pour passer la prochaine colonne
				if (solve(row, col + 1)){
					return true;
				}
			}
		}
	}
	
	// si on remplit pas les valeurs suite à la fonction , on reprint 0
	grid[row][col] = 0;
	
	return false;
}


// main function
int main (int argc, const char * argv[]) {

	// on initialise le temps pour l'execution
    float temps;
    clock_t t1, t2;
 
    t1 = clock();

	// si il n'y a pas de fichier d'entrée
	if (argc != 2) {
		printf("Usage: '--random'or '/path/to/sudoku_{level}.txt'\n");
		
		return EXIT_SUCCESS;
	}else{
		char realPath[PATH_MAX + 1];
		char *tmp = realpath(argv[1], realPath);

		char *res = (char*)malloc(100);
		res = tmp;

		if(strcmp(argv[1] ,"--random" ) == 0){
			free(res);
			startGenerate();
			res = realpath("sudoku_grid/random.txt", realPath);
		}
		
		// si le lien n'est pas valide
		if (!res) {
			printf("%s%s","Invalid sudoku path!, it was : ", argv[1]);
			return EXIT_FAILURE;
		}

		// si le chargement du fichier n'est pas valide ou son contenu
		if (!sudokuFile(realPath)) {
			printf("Couldn't load the sudoku!\n");
			
			return EXIT_FAILURE;
		}else{
			// on commence à résoudre à partir de 0 
			if(solve(0,0)){
				int ctn_pipe = 1;
				int ctn_bar = 1;
				// on parcours tout
				printf(YELLOW "*" RESET);
				printf(MAGENTA "-----------------------" RESET);
				printf(YELLOW "*\n" RESET);
				for (int row = 0; row < ROWS; row++) {
					printf(MAGENTA "| " RESET);
					for (int col = 0; col < COLS; col++) {
						// on print la grille
						printf(CYAN);
						printf("%d ",grid[row][col]);
						printf(RESET);
						if(ctn_pipe % 3 == 0){
							printf(MAGENTA "| " RESET);
						}
						ctn_pipe++;
					}
					if(ctn_bar % 3 == 0){
						printf(YELLOW "\n*" RESET);
						printf(MAGENTA "-----------------------" RESET);
						printf(YELLOW "*" RESET);
					}
					printf("\n");
					ctn_bar++;
				}
				// si aucun solution trouvée
			}else{
				printf("I have no solution !");
			}
		}

	}

    t2 = clock();
	// calcul du temps avec clock de time.h
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;

	printf("time = %f\n", temps);
	
	return EXIT_SUCCESS;
}