
#include "../inc/SudokuCell.h"
#include "../inc/SudokuGrid.h"
#include <time.h>

#define SUDOKU_GRID_SIZE 81

typedef struct _Sudoku_Grid
{
    int missing;
    Sudoku_Cell **cells;
} _Sudoku_Grid;

Sudoku_Grid *sudoku_grid_create(void)
{
    _Sudoku_Grid *grid = calloc(1, sizeof(_Sudoku_Grid *));
    grid->cells = calloc(SUDOKU_GRID_SIZE, sizeof(Sudoku_Cell *));
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
    DBG("Sudoku grid created successfully");

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

static int *sudoku_grid_generate_diagonal(void)
{
    int r_min = 0, r_max = 3, c_min = 0, c_max = 3;
    int *cells = calloc(SUDOKU_GRID_SIZE, sizeof(int));
    int taken[10];

    if (!cells)
        return NULL;

    srand(time(NULL)); // reset seed

    while (r_min < 9) // this will loop 3 times
    {
        memset(taken, 0, 10 * sizeof(10)); // reset taken list

        for (int ii = r_min; ii < r_max; ii++)
        {
            for (int jj = c_min; jj < c_max; jj++)
            {
                int v;
                do
                {
                    v = (rand() % 9) + 1;
                } while (taken[v]);
                taken[v] = 1;
                cells[SUDOKU_CELL_RC_TO_INDEX(ii, jj)] = v;
            }
        }

        r_min = r_max;
        r_max += 3;
        c_min = c_max;
        c_max += 3;
    }
    return cells;
}

static bool sudoku_grid_check_if_valid(int *cells, int v, int index)
{
    int r, c;
    SUDOKU_CELL_INDEX_TO_RC(index, r, c);
    int r_min = (r / 3) * 3;
    int r_max = r_min + 3;
    int c_min = (c / 3) * 3;
    int c_max = c_min + 3;

#define SUDOKU_GRID_VALIDATE_AT(index, r, c)          \
    {                                                 \
        int n_ind = SUDOKU_CELL_RC_TO_INDEX(r, c);    \
        if (n_ind == index)                           \
            continue; /* skip same cell */            \
                                                      \
        /* Same value not allowed */                  \
        if (v == cells[n_ind])                        \
        {                                             \
            return false;                             \
        }                                             \
    }

    // validate row
    for (int ii = 0; ii < 9; ii++)
    {
        SUDOKU_GRID_VALIDATE_AT(index, ii, c);
    }

    // validate col
    for (int ii = 0; ii < 9; ii++)
    {
        SUDOKU_GRID_VALIDATE_AT(index, r, ii);
    }

    // validate block
    for (int ii = r_min; ii < r_max; ii++)
    {
        for (int jj = c_min; jj < c_max; jj++)
        {
            SUDOKU_GRID_VALIDATE_AT(index, ii, jj);
        }
    }

    return true;
#undef SUDOKU_GRID_VALIDATE_AT
}

static bool sudoku_grid_fill_grid_rec(int *cells, int r, int c)
{
    if (c >= 9 && r < 9 - 1)
    {
        r = r + 1;
        c = 0;
    }

    if (r >= 9 && c >= 9)
        return true;

    if (r < 3)
    {
        if (c < 3)
            c = 3;
    }
    else if (r < 9 - 3)
    {
        if (c == (int)(r / 3) * 3)
            c = c + 3;
    }
    else
    {
        if (c == 9 - 3)
        {
            r = r + 1;
            c = 0;
            if (r >= 9)
                return true;
        }
    }

    for (int num = 1; num <= 9; num++)
    {
        if (sudoku_grid_check_if_valid(cells, num, SUDOKU_CELL_RC_TO_INDEX(r, c)))
        {
            cells[SUDOKU_CELL_RC_TO_INDEX(r, c)] = num;
            if (sudoku_grid_fill_grid_rec(cells, r, c + 1))
                return true;

            cells[SUDOKU_CELL_RC_TO_INDEX(r, c)] = 0;
        }
    }
    return false;
}

static void sudoku_grid_fill_grid(int *cells)
{
    sudoku_grid_fill_grid_rec(cells, 0, 3);
}

int sudoku_grid_generate(Sudoku_Grid *grid)
{
    _Sudoku_Grid *grid_o = (_Sudoku_Grid *)grid;
    int *cells = NULL;
    int index = 0;

    if (!grid_o)
        return 1;

    DBG("Generate diagonal!");
    cells = sudoku_grid_generate_diagonal();

    if (!cells)
        return 2;

    DBG("Generate rest of grid!");
    sudoku_grid_fill_grid(cells);

    DBG("Fill grid with new values!");
    while (index < SUDOKU_GRID_SIZE)
    {
        int r, c;
        SUDOKU_CELL_INDEX_TO_RC(index, r, c);
        if (!(grid_o->cells[index]))
        {
            grid_o->cells[index] = sudoku_cell_create(-1, cells[index], true, index);
            if (!grid_o->cells[index])
                return 2;
        }
        else
        {
            if (sudoku_cell_correct_set(grid_o->cells[index], cells[index]))
                return 2;
            if (sudoku_cell_value_set(grid_o->cells[index], cells[index]))
                return 2;
        }
        index++;
    }

    return 0;
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

#define SUDOKU_GRID_VALIDATE_AT(index, r, c)                                                  \
    {                                                                                         \
        int n_ind = SUDOKU_CELL_RC_TO_INDEX(r, c);                                            \
        if (n_ind == index)                                                                   \
            continue; /* skip same cell */                                                    \
                                                                                              \
        /* Incomplete grid not allowed */                                                     \
        if (!grid_o->cells[n_ind])                                                            \
        {                                                                                     \
            DBGF("Incomplete grid (%d, %d)\n", index, r + 1, c + 1);                          \
            return false;                                                                     \
        }                                                                                     \
                                                                                              \
        /* Same value not allowed */                                                          \
        if (v == sudoku_cell_value_get(grid_o->cells[n_ind]))                                 \
        {                                                                                     \
            int rr, cc;                                                                       \
            SUDOKU_CELL_INDEX_TO_RC(index, rr, cc);                                           \
            DBGF("Same value %d @ (%d, %d) and (%d, %d)\n", v, rr + 1, cc + 1, r + 1, c + 1); \
            return false;                                                                     \
        }                                                                                     \
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
    _Sudoku_Grid *grid_o = (_Sudoku_Grid *)grid;
    int index = 0;
    int v;

    if (!grid_o)
        return NULL;

    outBuf = calloc(SUDOKU_GRID_SIZE * 3, sizeof(char));

    while (index < SUDOKU_GRID_SIZE)
    {
        if (grid_o->cells[index])
            v = sudoku_cell_value_get(grid_o->cells[index]);
        sprintf(outBuf + index * 2, "%d%s",
                (v >= 1 && v <= 9) ? v : 0,
                (!((index + 1) % 9)) ? "\n" : " ");
        index++;
    }
    return outBuf;
}
