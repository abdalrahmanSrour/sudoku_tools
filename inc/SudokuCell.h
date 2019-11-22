#ifndef _SUDOKU_CELL_H_
#define _SUDOKU_CELL_H_

#include "Common.h"

typedef struct _Sudoku_Cell Sudoku_Cell;

/**
 * Converts @p row & @p col to sudoku grid index
 * Used with @ref sudoku_cell_create().
 * 
 * Usage:
 * sudoku_cell_create(5, 5, SUDOKU_CELL_RC_TO_INDEX(4, 5));
 */
#define SUDOKU_CELL_RC_TO_INDEX(row, col) ((row * 9) + col)

/**
 * Converts @p index to sudoku grid @p row, @p col
 */
#define SUDOKU_CELL_INDEX_TO_RC(index, row, col) do { row = index / 9; col = index % 9; } while(0);


/**
 * Create sudoku cell that hold the @p init value,
 * and expected @p correct value at @p index.
 * @p index can be translated to row and column.
 * @p init >= 0 and <= 9, otherwise correct value will be set
 * @p correct must be >= 1 and <= 9
 * @p index must be >= 0 and <= 80
 * 
 * @param init @type int: Initial value.
 * @param correct @type int: Expected correct value.
 * @param index @type int: index in grid, which can be
 *                         translated to/from row & column.
 * 
 * @return Sudoku_Cell*: handler for created sudoku cell.
 */
Sudoku_Cell *sudoku_cell_create(int init, int correct, bool readonly, int index);

/**
 * Deletes input @p cell.
 * 
 * @param cell @type Sudoku_Cell*: sudoku cell handler to delete.
 * 
 * @return void
 */
void sudoku_cell_del(Sudoku_Cell *cell);

/**
 * Set correct value, value should be >= 1 and <= 9
 * 
 * @param cell @type Sudoku_Cell*: sudoku cell handler
 * @param correct @type int: new value
 * 
 * @return int: whether value updated or not
 */
int sudoku_cell_correct_set(Sudoku_Cell *cell, int correct);

/**
 * Get correct value.
 * 
 * @param cell @type Sudoku_Cell*: sudoku cell handler
 * 
 * @return int: current correct value
 */
int sudoku_cell_correct_get(Sudoku_Cell *cell);

/**
 * Get Initial value.
 * 
 * @param cell @type Sudoku_Cell*: sudoku cell handler
 * 
 * @return int: Initial value set by @ref sudoku_cell_create()
 */
int sudoku_cell_init_get(Sudoku_Cell *cell);

/**
 * Set current value held by cell, this will override init value
 * if value equal to correct value, @ref sudoku_cell_is_correct() will return true
 * value won't change if readonly is false. see @ref sudoku_cell_create();
 * @p val must be >= 1 and <= 9
 * 
 * @param cell @type Sudoku_Cell*: sudoku cell handler
 * @param val @type int: new value for cell
 * 
 * @return int: 0 if value changed
 */
int sudoku_cell_value_set(Sudoku_Cell *cell, int val);

/**
 * Get current value held by cell.
 * If @ref sudoku_cell_value_set() didn't called before
 * this will return init value, see @ref sudoku_cell_create();
 * if readonly is true, this function will return correct value
 *
 * @param cell @type Sudoku_Cell*: sudoku cell handler
 *
 * @return int: current value held by cell
 */
int sudoku_cell_value_get(Sudoku_Cell *cell);

/**
 * Get current index.
 *
 * @param cell @type Sudoku_Cell*: sudoku cell handler
 *
 * @return int: current index
 */
int sudoku_cell_index_get(Sudoku_Cell *cell);

/**
 * Get current row & col.
 *
 * @param cell @type Sudoku_Cell*: sudoku cell handler
 * @param row @type int*: output to set row in it
 * @param col @type int*: output to set column in it
 *
 * @return int: current index
 */
void sudoku_cell_row_col_get(Sudoku_Cell *cell, int *row, int *col);

/**
 * Whether entered value is equal to correct value or not.
 * If cell is readonly this function will always return true
 *
 * @param cell @type Sudoku_Cell*: sudoku cell handler
 *
 * @return bool
 */
bool sudoku_cell_is_correct(Sudoku_Cell *cell);

/**
 * Whether cell is readonly or not.
 *
 * @param cell @type Sudoku_Cell*: sudoku cell handler
 *
 * @return bool
 */
bool sudoku_cell_is_readonly(Sudoku_Cell *cell);




#endif /* _SUDOKU_CELL_H_ */
