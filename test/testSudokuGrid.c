#include "../inc/SudokuGrid.h"
#include "../inc/Test.h"

unsigned char verboseMode = 1;
int number_of_test = 0;
int number_of_correct_tests = 0;

#define SIMPLE_GRID1 "1 2 3 4 5 6 7 8 9\n" \
                     "1 2 3 4 5 6 7 8 9\n" \
                     "1 2 3 4 5 6 7 8 9\n" \
                     "1 2 3 4 5 6 7 8 9\n" \
                     "1 2 3 4 5 6 7 8 9\n" \
                     "1 2 3 4 5 6 7 8 9\n" \
                     "1 2 3 4 5 6 7 8 9\n" \
                     "1 2 3 4 5 6 7 8 9\n" \
                     "1 2 3 4 5 6 7 8 "

#define SIMPLE_GRID2 "1 2 3 4 5 6 7 8 9\n"   \
                     "1 2 3 4 5 6 7 8 9\n"   \
                     "1 2 3 4 5 6 7 8 9\n"   \
                     "1 2 3 4 5 6 7 8 9\n"   \
                     "1 2 3 4 5 6 7 8 9\n"   \
                     "1 2 3 4 5 6 7 8 95 \n" \
                     "1 2 3 4 5 6 7 8 9 5\n" \
                     "1 2 3 4 5 6 7 8 9 5\n" \
                     "1 2 3 4 5 6 7 8 \n"    \
                     "1 2 3 4 5 6 7 8 9\n"

#define SIMPLE_GRID3 "1234567890-12\r\n"     \
                     "1234567890-12\r\n"     \
                     "1234567890-12\r"       \
                     "1234567890-12\n"       \
                     "1234567890-12\r"       \
                     "1234567890-12\r\n\n\n" \
                     "1234567890-12\n"       \
                     "1234567890-12\n"       \
                     "1234567890-12\n"

#define SIMPLE_GRID4 "+-------+-------+-------+\n" \
                     "\n"                          \
                     "| 5 3 4 | 6 7 8 | 9 1 2 |\n" \
                     "\n"                          \
                     "| 6 7 2 | 1 9 5 | 3 4 8 |\n" \
                     "\n"                          \
                     "| 1 9 8 | 3 4 2 | 5 6 7 |\n" \
                     "\n"                          \
                     "+-------+-------+-------+\n" \
                     "\n"                          \
                     "| 8 5 9 | 7 6 1 | 4 2 3 |\n" \
                     "\n"                          \
                     "| 4 2 6 | 8 5 3 | 7 9 1 |\n" \
                     "\n"                          \
                     "| 7 1 3 | 9 2 4 | 8 5 6 |\n" \
                     "\n"                          \
                     "+-------+-------+-------+\n" \
                     "\n"                          \
                     "| 9 6 1 | 5 3 7 | 2 8 4 |\n" \
                     "\n"                          \
                     "| 2 8 7 | 4 1 9 | 6 3 5 |\n" \
                     "\n"                          \
                     "| 3 4 5 | 2 8 6 | 1 7 9 |\n" \
                     "\n"                          \
                     "+-------+-------+-------+"

#define SIMPLE_GRID4_RES "5 3 4 6 7 8 9 1 2\n" \
                         "6 7 2 1 9 5 3 4 8\n" \
                         "1 9 8 3 4 2 5 6 7\n" \
                         "8 5 9 7 6 1 4 2 3\n" \
                         "4 2 6 8 5 3 7 9 1\n" \
                         "7 1 3 9 2 4 8 5 6\n" \
                         "9 6 1 5 3 7 2 8 4\n" \
                         "2 8 7 4 1 9 6 3 5\n" \
                         "3 4 5 2 8 6 1 7 9\n"

int main(int argc, char const *argv[])
{
    int r, c;
    char *buf;
    DBG("Start Sudoku_Grid tester");

    TEST_START();

    Sudoku_Grid *grid = sudoku_grid_create_from_str(SIMPLE_GRID1);

    FAIL_EQ(NULL, grid);

    grid = sudoku_grid_create_from_str(SIMPLE_GRID2);

    FAIL_NE(NULL, grid);
    FAIL_NE(true, sudoku_grid_is_valid(grid));

    sudoku_grid_del(&grid);

    grid = sudoku_grid_create_from_str(SIMPLE_GRID3);

    FAIL_NE(NULL, grid);
    FAIL_NE(true, sudoku_grid_is_valid(grid));

    sudoku_grid_del(&grid);

    grid = sudoku_grid_create_from_str(SIMPLE_GRID4);

    FAIL_NE(NULL, grid);
    FAIL_EQ(true, sudoku_grid_is_valid(grid));

    buf = sudoku_grid_print(grid);

    FAIL_NE(NULL, buf);
    FAIL_STR_EQ(buf, SIMPLE_GRID4_RES);

    if (buf) free(buf);

    sudoku_grid_del(&grid);

    TEST_FINISH();
    return 0;
}
