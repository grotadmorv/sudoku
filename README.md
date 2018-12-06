# sudoku

You can find some sudoku grid in /sudoku_grid/

Execution time with my program : 
- sudoku_easy : `0.000000s`
- sudoku_medium : `0.000000s`
- sudoku_hard : `12.000000s` // optimize in progress
- sudoku_random : `0.000000s`
- 'most_difficult_sudoku_in_world' : `0.000000s` // publish in 2006

run on Linux
- `gcc -o main main.c` 
- `./main sudoku_grid/sudoku_{level}.txt` // for your own file
- `./a.exe --random`  // random grid and resolve itself

run on Windows(Cygwin64)
- `g++ -std=gnu++11 main.c`
- `./a.exe sudoku_grid/sudoku_{level}.txt` // for your own file
- `./a.exe --random`  // random grid and resolve itself
