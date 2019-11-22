#ifndef _SUDOKU_GRID_H_
#define _SUDOKU_GRID_H_

#include "Common.h"

typedef struct _Sudoku_Grid Sudoku_Grid;

/**
 * Create and return new Sudoku_Grid object.
 * 
 * see also @ref sudoku_grid_create_from_str()
 * 
 * @return Sudoku_Grid*: sudoku grid object handler.
 */
Sudoku_Grid *sudoku_grid_create(void);

/**
 * Create and return new Sudoku_Grid Object from
 * @p string. String must have atleast 9 valid lines
 * each line must have 9 digits
 * non-digits, white spaces, empty lines will be ignored, 
 * and lines with less than 9 digits will be ignored
 * as well.
 * if valid lines are less than 9, this function will return NULL
 * if digit is equal to 0, the cell will be editable. Otherwise
 * editing cells not allowed.
 * 
 * 1 2 3 4 5 6 7 8 9 << valid line
 * 123456789 << valid line
 * 1234 << invalid
 * -------- << invalid
 * <empty> << invalid
 * | 1 2 3 | 4 5 6 | 7 8 9 | << valid
 * +1-2-3+4-5-6+7-8-9+ << valid line
 * 
 * see also @ref sudoku_grid_create()
 * 
 * @param str @type const char*: input string
 * 
 * @return Sudoku_Grid*: sudoku grid object handler.
 */
Sudoku_Grid *sudoku_grid_create_from_str(const char *str);

/**
 * Delete Sudoku_Grid object @p grid.
 * 
 * @param grid @type Sudoku_Grid*: sudoku grid object handler.
 * 
 * @return void
 */
void sudoku_grid_del(Sudoku_Grid **grid);

/**
 * This will generate new values for Sudoku_Grid object @p grid
 * 
 * @param grid @type Sudoku_Grid*: sudoku grid object handler.
 * 
 * @return int: 0 on success
 *              1 if @p grid is null
 *              2 otherwise
 */
int sudoku_grid_generate(Sudoku_Grid *grid);

/**
 * This will update the value of cell at @p row, and @p col
 * with new value @p val. If and only if the cell is editable
 * 
 * @param grid @type Sudoku_Grid*: sudoku grid object handler.
 * @param row @type int: row number (0 -> 8)
 * @param col @type int: column number (0 -> 8)
 * @param val @type int: new value (1 -> 9)
 * 
 * @return int: 0 on success
 *              1 if @p grid is null
 *              2 if row or col is invalid
 *              3 if val is not valid
 *              4 if cell is not editable
 *              5 otherwise
 */
int sudoku_grid_update_at(Sudoku_Grid *grid, int row, int col, int val);

/**
 * Return value at given @p row & @p col.
 * 
 * @param grid @type Sudoku_Grid*: sudoku grid object handler.
 * @param row @type int: row number 1-9
 * @param col @type int: column number 1-9
 * 
 * @return int: value at (row, col)
 *              -1 otherwise
 */
int sudoku_grid_value_at_get(Sudoku_Grid *grid, int row, int col);

/**
 * Return number of missing items
 * 
 * @param grid @type Sudoku_Grid*: sudoku grid object handler.
 * 
 * @return int: number of missing items
 *              -1 otherwise
 */
int sudoku_grid_missing_get(Sudoku_Grid *grid);

/**
 * Whether @p grid holds completed grid or not
 * 
 * @param grid @type Sudoku_Grid*: sudoku grid object handler.
 * 
 * @return bool
 */
bool sudoku_grid_is_correct(Sudoku_Grid *grid);

/**
 * Whether @p grid is valid or not
 * 
 * @param grid @type Sudoku_Grid*: sudoku grid object handler.
 * 
 * @return bool
 */
bool sudoku_grid_is_valid(Sudoku_Grid *grid);

/**
 * This will print the @p grid into new buffer and return it.
 * User must free returned buffer after using it.
 * 
 * @param grid @type Sudoku_Grid*: sudoku grid object handler.
 * 
 * @return char*: NULL if grid is NULL
 */
char *sudoku_grid_print(Sudoku_Grid *grid);

#endif /* _SUDOKU_GRID_H_ */
