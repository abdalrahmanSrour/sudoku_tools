
#include "../inc/SudokuCell.h"
#include "../inc/SudokuGrid.h"

#define SUDOKU_GRID_SIZE 81

typedef struct _Sudoku_Grid
{
    Sudoku_Cell **cells;
    int missing;
} _Sudoku_Grid;

Sudoku_Grid *sudoku_grid_create(void)
{
    _Sudoku_Grid *grid = calloc(1, sizeof(_Sudoku_Grid *));
    grid->cells = calloc(SUDOKU_GRID_SIZE, sizeof(Sudoku_Cell*));
    grid->missing = 0;

    return (Sudoku_Grid *)grid;
}

static int *sudoku_grid_parse_grid(const char *str)
{
    char *p = (char *)str;
    int row = 0, col = 0;
    int *list = calloc(SUDOKU_GRID_SIZE, sizeof(int));

    if (!p || !list)
        goto PARSING_EXIT;

    while (*p)
    {
        if (*p == '\n' || *p == '\r')
        {
            // Unexpected end of line, drop parsed digits from this line
            col = 0;
        }
        else if (col < 9                    // don't parse more than 9 numbers
                 && *p >= '0' && *p <= '9') // only digits is allowed
        {
            list[SUDOKU_CELL_RC_TO_INDEX(row, col)] = *p - '0';
            col++;
        }

        if (col >= 9)
        {
            col = 0;
            row++;

            if (row >= 9)
            {
                // parsing finished
                return list;
            }

            // New line? skip to next line
            while (*p)
            {
                if (*p == '\n')
                    break;
                if (*p == '\r')
                {
                    if (*(p + 1) && *p == '\n')
                        p++;
                    break;
                }
                p++;
            }
        }
        p++;
    }

    goto PARSING_EXIT;

PARSING_EXIT:
    if (list)
        free(list);
    DBG("Can't create sudoku grid!");
    return NULL;
}

Sudoku_Grid *sudoku_grid_create_from_str(const char *str)
{
    int *pars_vals = NULL;
    if (!str)
        return NULL;
    DBG("Creating sudoku grid from str");

    if (!(pars_vals = sudoku_grid_parse_grid(str)))
        return NULL;

    _Sudoku_Grid *grid = (_Sudoku_Grid *)sudoku_grid_create();

    grid->missing = 0;

    for (int ii = 0; ii < SUDOKU_GRID_SIZE; ii++)
    {
        // DBGF("Add value %d @ %d (%d, %d) missing=%d\n", pars_vals[ii], ii, ii / 9, ii % 9, grid->missing);
        if (pars_vals[ii] > 0 && pars_vals[ii] < 10)
            grid->cells[ii] = sudoku_cell_create(-1, pars_vals[ii], true, ii);
        else
        {
            grid->cells[ii] = sudoku_cell_create(0, pars_vals[ii], false, ii);
            grid->missing++;
        }
    }
    DBG("Sudoku grid created succesfully");

    return (Sudoku_Grid *)grid;
}

void sudoku_grid_del(Sudoku_Grid **grid)
{
    _Sudoku_Grid *grid_o = (_Sudoku_Grid *)*grid;

    if (!grid_o)
        return;

    for (int ii = 0; ii < SUDOKU_GRID_SIZE; ii++)
    {
        // DBGF("free value %d @ (%d, %d)\n", sudoku_cell_value_get(grid_o->cells[ii]), ii / 9, ii % 9);
        if (grid_o->cells[ii])
            sudoku_cell_del(grid_o->cells[ii]);
        grid_o->cells[ii] = NULL;
    }

    free(*grid); // FIXME: this cause seg error!
    *grid = NULL;
}

int sudoku_grid_generate(Sudoku_Grid *grid)
{
#warning "Not implemented"
}

int sudoku_grid_update_at(Sudoku_Grid *grid, int row, int col, int val)
{
    _Sudoku_Grid *grid_o = (_Sudoku_Grid *)grid;
    int ret = 0;

    if (!grid_o)
        return 1;

    int index = SUDOKU_CELL_RC_TO_INDEX(row, col);

    if (index < 0 || index >= SUDOKU_GRID_SIZE)
        return 2;
    if (!(val >= 1 && val <= 9))
        return 3;

    if (grid_o->cells[index])
    {
        if (sudoku_cell_is_readonly(grid_o->cells[index]))
            return 4;

        if (sudoku_cell_is_correct(grid_o->cells[index]))
            grid_o->missing++;

        sudoku_cell_value_set(grid_o->cells[index], val);

        if (sudoku_cell_is_correct(grid_o->cells[index]))
            grid_o->missing--;

        return 0;
    }
    else
    {
        // create new one
        grid_o->cells[index] = sudoku_cell_create(val, val, false, index);
    }

    return 5;
}

int sudoku_grid_value_at_get(Sudoku_Grid *grid, int row, int col)
{
    _Sudoku_Grid *grid_o = (_Sudoku_Grid *)grid;

    if (!grid_o)
        return -1;

    int index = SUDOKU_CELL_RC_TO_INDEX(row, col);

    if (index < 0 || index >= SUDOKU_GRID_SIZE)
        return -1;

    if (grid_o->cells[index])
    {
        return sudoku_cell_value_get(grid_o->cells[index]);
    }

    return -1;
}

int sudoku_grid_missing_get(Sudoku_Grid *grid)
{
    _Sudoku_Grid *grid_o = (_Sudoku_Grid *)grid;

    if (!grid_o)
        return -1;

    return grid_o->missing;
}

bool sudoku_grid_is_correct(Sudoku_Grid *grid)
{
    _Sudoku_Grid *grid_o = (_Sudoku_Grid *)grid;
    int index = 0;

    if (!grid_o)
        return false;

    while (index < SUDOKU_GRID_SIZE)
    {
        if (!sudoku_cell_is_correct(grid_o->cells[index]))
            return false;
        index++;
    }

    return true;
}

bool sudoku_grid_is_valid(Sudoku_Grid *grid)
{
    _Sudoku_Grid *grid_o = (_Sudoku_Grid *)grid;
    int index = 0;

    if (!grid_o)
        return false;

    while (index < SUDOKU_GRID_SIZE)
    {
        int r, c;
        int v = sudoku_cell_value_get(grid_o->cells[index]);
        SUDOKU_CELL_INDEX_TO_RC(index, r, c);

#define SUDOKU_GRID_VALIDATE_AT(index, r, c)                      \
    {                                                             \
        int n_ind = SUDOKU_CELL_RC_TO_INDEX(r, c);                \
        if (n_ind == index)                                       \
            continue; /* skip same cell */                        \
                                                                  \
        /* Incomplete grid not allowed */                         \
        if (!grid_o->cells[n_ind])                                \
        {                                                         \
            DBGF("Incomplete grid %d @ (%d, %d)\n", index, r, c); \
            return false;                                         \
        }                                                         \
                                                                  \
        /* Same value not allowed */                              \
        if (v == sudoku_cell_value_get(grid_o->cells[n_ind]))     \
        {                                                         \
            DBGF("Same value %d @ (%d, %d)\n", index, r, c); \
            return false;                                         \
        }                                                         \
    }

        // DBG("validate Row");
        // validate row
        for (int ii = 0; ii < 9; ii++)
        {
            SUDOKU_GRID_VALIDATE_AT(index, ii, c);
        }

        // DBG("validate Col");
        // validate col
        for (int ii = 0; ii < 9; ii++)
        {
            SUDOKU_GRID_VALIDATE_AT(index, r, ii);
        }

        int r_min = (r / 3) * 3;
        int r_max = r_min + 3;
        int c_min = (c / 3) * 3;
        int c_max = c_min + 3;

        // DBGF("validate block from (%d, %d) to (%d, %d)\n", r_min, c_min, r_max, c_max);
        // validate block
        for (int ii = r_min; ii < r_max; ii++)
        {
            for (int jj = c_min; jj < c_max; jj++)
            {
                SUDOKU_GRID_VALIDATE_AT(index, ii, jj);
            }
        }

        index++;
    }

    return true;
}

char *sudoku_grid_print(Sudoku_Grid *grid)
{
    char *outBuf = NULL;
    _Sudoku_Grid *grid_o = (_Sudoku_Grid*) grid;
    int index = 0;

    if (!grid_o) return NULL;

    outBuf = calloc(SUDOKU_GRID_SIZE * 3, sizeof(char));

    while (index < SUDOKU_GRID_SIZE)
    {
        sprintf(outBuf + index * 2, "%d%s", 
                (grid_o->cells[index]) ? sudoku_cell_value_get(grid_o->cells[index]) : 0,
                (!((index + 1) % 9)) ? "\n" : " ");
        index ++;
    }
    return outBuf;
}
