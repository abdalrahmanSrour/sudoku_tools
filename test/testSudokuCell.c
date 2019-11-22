#include "../inc/SudokuCell.h"
#include "../inc/Test.h"

unsigned char verboseMode = 1;
int number_of_test = 0;
int number_of_correct_tests = 0;

int main(int argc, char const *argv[])
{
    int r, c;
    DBG("Start Sudoku_Cell tester");
    
    TEST_START();
    Sudoku_Cell *cell = sudoku_cell_create(-1, 5, true, SUDOKU_CELL_RC_TO_INDEX(0, 5));

    FAIL_EQ(5, sudoku_cell_value_get(cell));
    FAIL_EQ(true, sudoku_cell_is_readonly(cell));
    FAIL_EQ(5, sudoku_cell_index_get(cell));
    sudoku_cell_row_col_get(cell, &r, &c);
    FAIL_EQ(0, r);
    FAIL_EQ(5, c);

    FAIL_EQ(true, sudoku_cell_is_correct(cell));

    FAIL_EQ(1, sudoku_cell_value_set(cell, 50));

    FAIL_EQ(5, sudoku_cell_value_get(cell));
    FAIL_EQ(true, sudoku_cell_is_correct(cell));

    FAIL_EQ(1, sudoku_cell_value_set(cell, 9));

    FAIL_EQ(5, sudoku_cell_value_get(cell));
    FAIL_EQ(true, sudoku_cell_is_correct(cell));
    FAIL_EQ(true, sudoku_cell_is_readonly(cell));
    FAIL_EQ(5, sudoku_cell_index_get(cell));

    FAIL_EQ(0, sudoku_cell_correct_set(cell, 9));
    FAIL_EQ(9, sudoku_cell_value_get(cell));
    FAIL_EQ(true, sudoku_cell_is_correct(cell));

    sudoku_cell_del(cell);
    cell = NULL;
    FAIL_EQ(1, sudoku_cell_correct_set(cell, 9));

    
    cell = sudoku_cell_create(1, 6, false, SUDOKU_CELL_RC_TO_INDEX(7, 3));

    FAIL_EQ(1, sudoku_cell_value_get(cell));
    FAIL_EQ(false, sudoku_cell_is_readonly(cell));
    FAIL_EQ(SUDOKU_CELL_RC_TO_INDEX(7, 3), sudoku_cell_index_get(cell));
    sudoku_cell_row_col_get(cell, &r, &c);
    FAIL_EQ(7, r);
    FAIL_EQ(3, c);

    FAIL_EQ(false, sudoku_cell_is_correct(cell));

    FAIL_EQ(1, sudoku_cell_value_set(cell, 50));

    FAIL_EQ(1, sudoku_cell_value_get(cell));
    FAIL_EQ(false, sudoku_cell_is_correct(cell));

    FAIL_EQ(0, sudoku_cell_value_set(cell, 9));

    FAIL_EQ(9, sudoku_cell_value_get(cell));
    FAIL_EQ(false, sudoku_cell_is_correct(cell));
    FAIL_EQ(false, sudoku_cell_is_readonly(cell));
    FAIL_EQ(66, sudoku_cell_index_get(cell));

    FAIL_EQ(0, sudoku_cell_value_set(cell, 6));

    FAIL_EQ(6, sudoku_cell_value_get(cell));
    FAIL_EQ(true, sudoku_cell_is_correct(cell));

    FAIL_EQ(0, sudoku_cell_correct_set(cell, 9));
    FAIL_EQ(6, sudoku_cell_value_get(cell));
    FAIL_EQ(false, sudoku_cell_is_correct(cell));

    sudoku_cell_del(cell);
    cell = NULL;
    FAIL_EQ(1, sudoku_cell_correct_set(cell, 9));
    
    TEST_FINISH();
    return 0;
}
