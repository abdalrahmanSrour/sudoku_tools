# Sudoku Game Tools Written in C Language

> Made by Abed Srour <eng.abdsrour@gmail.com>

Tools for the awesome game Sudoku! :D

Written in C Language, built using `make` and `gcc` tools.

This repo has two tools:
1. [Sudoku Validator](#sudoku-validator): Validate sudoku grid.
2. [Sudoku Generator](#sudoku-generator): Generate new random sudoku grid.

> Binary built using Cygwin64 on Windows 10!

## Sudoku Validator
Sudoku Validator is a CLI tool that can be used to validate a Sudoku board, whether is it correct or not.
Input can be passed using *stdin* or *file*.

### Build
Using `make` tool, navigate to repository directory, then type the following command:
```sh
make
# or
make bin/SudokuValidator.exe
```
> To clean project use `make clean`

### Usage
Sudoku Validator can be used to read from *stdin* or *file*, as described in help message:
```
Sudoku grid validator, made by Abed Srour <eng.abdsrour@gmail.com>
---------------------------------------------------------------
Usage:
bin/SudokuValidator [-h] [-f file] [-v]
        -h                      Help: to show this help message!

        -f filePath             File: to read sudoku grid from file
                                Otherwise stdin will be used to read grid
                                to finish input using stdin just enter two times

        -v                      Verbose: to enable verbose mode
---------------------------------------------------------------
```
> To print help message, type `./bin/SudokuValidator -h`

#### Using Stdin
Run application without any arguments:
```sh
./bin/SudokuValidator
```
Application will ask to enter Sudoku grid, each line represent one row of digits
characters other than digits will be ignored, and if line does not have 9 digits
the line will be skipped, if less than 9 valid lines entered, the application
will show error message and exit.

Here is a sample input
```
+-------+-------+-------+
| 5 3 4 | 6 7 8 | 9 1 2 |
| 6 7 2 | 1 9 5 | 3 4 8 |
| 1 9 8 | 3 4 2 | 5 6 7 |
+-------+-------+-------+
| 8 5 9 | 7 6 1 | 4 2 3 |
| 4 2 6 | 8 5 3 | 7 9 1 |
| 7 1 3 | 9 2 4 | 8 5 6 |
+-------+-------+-------+
| 9 6 1 | 5 3 7 | 2 8 4 |
| 2 8 7 | 4 1 9 | 6 3 5 |
| 3 4 5 | 2 8 6 | 1 7 9 |
+-------+-------+-------+

```

> Don't forget to press on enter two times to finish input.

Another one
```
957 613 284
483 257 196
612 849 537
178 364 952
524 971 368
369 528 741
845 792 613
291 436 875
736 185 429
try me :)
```

#### Using Files
Run application with `-f` argument followed by filepath:
```sh
./bin/SudokuValidator -f samples/first.txt
```

This will read file and try to parse it, note here same rules applies as described in
[Using Stdin](#using-stdin), plus empty line will be ignored.

> There is 3 valid samples and 2 invalid samples in `samples` folder


## Sudoku Generator
Sudoku Generator is a CLI tool that can be used to generate a rando Sudoku board. it's
garanteed that generated grid is a valid Sudoku board.
Output can be to *stdout* or to *file*.

### Build
Using `make` tool, navigate to repository directory, then type the following command:
```sh
make
# or
make bin/SudokuGenerator.exe
```
> To clean project use `make clean`

### Usage
Sudoku Ganerator can be used to write on *stdout* or *file*, as described in help message:
```
Sudoku grid generator, made by Abed Srour <eng.abdsrour@gmail.com>
---------------------------------------------------------------
Usage:
bin/SudokuGenerator [-h] [-f file] [-v]
        -h                      Help: to show this help message!

        -f filePath             File: to write sudoku grid to file
                                Otherwise stdout will be used to show grid

        -v                      Verbose: to enable verbose mode
---------------------------------------------------------------
```
> To print help message, type `./bin/SudokuGenerator -h`

#### Print to Stdout
Run application without any arguments:
```sh
./bin/SudokuGenerator
```
Application will generate new sudoku grid randomly and print it into stdout.

Here is a sample output
```
Sudoku grid generated successfuly! horaay :)
Generated using SudokuGenerator, created by Abed Srour <eng.abdsrour@gmail.com>
6 3 9 1 4 2 5 7 8
4 1 8 5 3 7 2 9 6
2 5 7 6 9 8 1 3 4
3 4 6 9 2 5 7 8 1
5 8 2 7 6 1 3 4 9
7 9 1 3 8 4 6 5 2
8 6 5 4 1 3 9 2 7
9 2 3 8 7 6 4 1 5
1 7 4 2 5 9 8 6 3

```
> Try to validate it using [Sudoku Validator](#sudoku-validator)

#### Print to File
Run application with `-f` argument followed by filepath:
```sh
./bin/SudokuGenerator -f out.txt
```

This will write generated sudoku grid to file.
