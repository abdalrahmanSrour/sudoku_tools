CC=gcc
CFLAGS=-I. 
INC=inc
SRC=src
OBJ=obj
BIN=bin
TST=test

DEPS = $(INC)/Common.h $(INC)/SudokuGrid.h $(INC)/SudokuCell.h 

all: $(BIN)/SudokuValidator.exe $(BIN)/SudokuGenerator.exe

$(BIN)/SudokuValidator.exe: $(OBJ)/SudokuGrid.o $(OBJ)/SudokuCell.o $(OBJ)/SudokuValidator.o $(DEPS)
	$(CC) -o $@ $(OBJ)/SudokuGrid.o $(OBJ)/SudokuCell.o $(OBJ)/SudokuValidator.o $(CFLAGS)

$(BIN)/SudokuGenerator.exe: $(OBJ)/SudokuGrid.o $(OBJ)/SudokuCell.o $(OBJ)/SudokuGenerator.o $(DEPS)
	$(CC) -o $@ $(OBJ)/SudokuGrid.o $(OBJ)/SudokuCell.o $(OBJ)/SudokuGenerator.o $(CFLAGS)

test: $(TST)/testSudokuCell.exe
	$(TST)/testSudokuCell.exe

$(TST)/testSudokuCell.exe: $(OBJ)/SudokuGrid.o $(OBJ)/SudokuCell.o $(TST)/testSudokuCell.o $(DEPS) $(INC)/Test.h
	$(CC) -o $@ $(OBJ)/SudokuGrid.o $(OBJ)/SudokuCell.o $(TST)/testSudokuCell.o $(CFLAGS)

# $(OBJ)/SudokuCell.o: $(SRC)/SudokuCell.c $(DEPS)
#      $(CC) -o $(BIN)/SudokuValidator.exe $< $(CFLAGS)

$(OBJ)/%.o: $(SRC)/%.c $(DEPS) $(INC)/Test.h
	$(CC) -g -O0 -c -o $@ $< $(CFLAGS)

$(TST)/%.o: $(TST)/%.c $(DEPS)
	$(CC) -g -O0 -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ)/*.o $(BIN)/*.exe $(TST)/*.o $(TST)/*.exe
