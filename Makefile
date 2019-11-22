CC=gcc
CFLAGS=-I. 
INC=inc
SRC=src
OBJ=obj
BIN=bin

DEPS = $(INC)/Common.h $(INC)/SudokuGrid.h $(INC)/SudokuCell.h 

all: SudokuValidator SudokuGenerator

SudokuValidator: $(OBJ)/SudokuGrid.o $(OBJ)/SudokuCell.o $(OBJ)/SudokuValidator.o $(DEPS)
	$(CC) -o $(BIN)/SudokuValidator.exe $(OBJ)/SudokuGrid.o $(OBJ)/SudokuCell.o $(OBJ)/SudokuValidator.o $(CFLAGS)

SudokuGenerator: $(OBJ)/SudokuGrid.o $(OBJ)/SudokuCell.o $(OBJ)/SudokuGenerator.o $(DEPS)
	$(CC) -o $(BIN)/SudokuGenerator.exe $(OBJ)/SudokuGrid.o $(OBJ)/SudokuCell.o $(OBJ)/SudokuGenerator.o $(CFLAGS)

# $(OBJ)/SudokuCell.o: $(SRC)/SudokuCell.c $(DEPS)
#      $(CC) -o $(BIN)/SudokuValidator.exe $< $(CFLAGS)

$(OBJ)/%.o: $(SRC)/%.c $(DEPS)
	$(CC) -g -O0 -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ)/*.o $(BIN)/*.exe
