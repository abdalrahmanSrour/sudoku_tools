#include "../inc/SudokuCell.h"

#define SUDOKU_CELL_VAL_CHECK(v) ((v > 0) && (v < 10))

typedef struct _SUDOKU_CELL
{
    int init;
    int correct;
    int index;
    int value;
    bool readonly;
} _SUDOKU_CELL;

Sudoku_Cell *sudoku_cell_create(int init, int correct, bool readonly, int index)
{
    _SUDOKU_CELL *cell = calloc(1, sizeof(_SUDOKU_CELL));
    cell->correct = (SUDOKU_CELL_VAL_CHECK(correct)) ? correct : -1;
    cell->init = (SUDOKU_CELL_VAL_CHECK(init)) ? init : (init == 0) ? 0 : correct;
    cell->readonly = readonly;
    cell->index = (index >= 0 && index <= 80) ? index : -1;
    cell->value = cell->init;

    return (Sudoku_Cell *)cell;
}

void sudoku_cell_del(Sudoku_Cell *cell)
{
    if (!cell)
        return;

    free(cell);
}

int sudoku_cell_correct_set(Sudoku_Cell *cell, int correct)
{
    _SUDOKU_CELL *cell_o = (_SUDOKU_CELL *)cell;
    if (!cell_o)
        return -1;
    if (!SUDOKU_CELL_VAL_CHECK(correct))
        return -1;

    cell_o->correct = correct;
    return 0;
}

int sudoku_cell_correct_get(Sudoku_Cell *cell)
{
    _SUDOKU_CELL *cell_o = (_SUDOKU_CELL *)cell;
    if (!cell_o)
        return -1;

    return cell_o->correct;
}

int sudoku_cell_init_get(Sudoku_Cell *cell)
{
    _SUDOKU_CELL *cell_o = (_SUDOKU_CELL *)cell;
    if (!cell_o)
        return -1;

    return cell_o->init;
}

int sudoku_cell_value_set(Sudoku_Cell *cell, int val)
{
    _SUDOKU_CELL *cell_o = (_SUDOKU_CELL *)cell;
    if (!cell_o || cell_o->readonly)
        return -1;
    if (!SUDOKU_CELL_VAL_CHECK(val))
        return -1;

    cell_o->value = val;
    return 0;
}

int sudoku_cell_value_get(Sudoku_Cell *cell)
{
    _SUDOKU_CELL *cell_o = (_SUDOKU_CELL *)cell;
    if (!cell_o)
        return -1;

    return (cell_o->readonly) ? cell_o->correct : cell_o->value;
}

int sudoku_cell_index_get(Sudoku_Cell *cell)
{
    _SUDOKU_CELL *cell_o = (_SUDOKU_CELL *)cell;
    if (!cell_o)
        return -1;

    return cell_o->index;
}

void sudoku_cell_row_col_get(Sudoku_Cell *cell, int *row, int *col)
{
    _SUDOKU_CELL *cell_o = (_SUDOKU_CELL *)cell;
    if (!cell_o)
        return;

    int r, c;

    SUDOKU_CELL_INDEX_TO_RC(cell_o->index, r, c);

    if (row)
        *row = r;
    if (col)
        *col = c;
}

bool sudoku_cell_is_correct(Sudoku_Cell *cell)
{
    _SUDOKU_CELL *cell_o = (_SUDOKU_CELL *)cell;
    if (!cell_o)
        return false;

    return (cell_o->readonly) ? true : cell_o->correct == cell_o->value;
}

bool sudoku_cell_is_readonly(Sudoku_Cell *cell)
{
    _SUDOKU_CELL *cell_o = (_SUDOKU_CELL *)cell;
    if (!cell_o)
        return false;

    return cell_o->readonly;
}