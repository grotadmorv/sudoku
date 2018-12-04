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


//chargement du fichier et du contenu
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


// valid function
int valid (int row, int col, int val) {

	// parcours des lignes
	for (int n = 0; n < rows; n++) {
		// si ça n ligne de la colonne ou n colonne de la ligne est egal à la valeur d'entrée, on renvoit faux 
		// --> solve passera à la suite
		if (grid[n][col] == val || grid[row][n] == val){
            return false;
        }
	}

	// modulo(reste) des lignes et colonnes

	int tmp_row = (row / box_width) * box_width;
	int tmp_col = (col / box_width) * box_width;
	

	// on parcours tout
	for (int r = tmp_row; r < tmp_row + box_width; r++) {
		for (int c = tmp_col; c < tmp_col + box_width; c++) {
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
	if (row == rows){
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
	for (int val = 1; val <= values; val++) {
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
		printf("Usage: sudoku /path/to/sudoku.txt\n");
		
		return EXIT_SUCCESS;
	}
	
	char realPath[PATH_MAX + 1];
	char *res = realpath(argv[1], realPath);
	
	// si le lien n'est pas valide
	if (!res) {
		printf("Invalid sudoku path!\n");
		
		return EXIT_FAILURE;
	}
	

	// si le chargement du fichier n'est pas valide ou son contenu
	if (!sudokuFile(realPath)) {
		printf("Couldn't load the sudoku!\n");
		
		return EXIT_FAILURE;
	}else{
		// on commence à résoudre à partir de 0 
		if(solve(0,0)){
			// on parcours tout
			for (int row = 0; row < rows; row++) {
				for (int col = 0; col < cols; col++) {
					// on print la grille
					printf("%d ", grid[row][col]);
				}
				
				printf("\n");
			}
			// si aucun solution trouvée
		}else{
			printf("I have no solution !");
		}
    }

    t2 = clock();
	// calcul du temps avec clock de time.h
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	
	printf("time = %f\n", temps);
	
	return EXIT_SUCCESS;
}