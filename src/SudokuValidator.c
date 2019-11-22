#include "../inc/Common.h"
#include "../inc/SudokuGrid.h"

unsigned char verboseMode = 0;
const char *filename = NULL;
const char *appname = NULL;

#define MAX_BUF_SIZE (128 * 64)

void readGridFrom(FILE *file, char *buf, size_t maxSize)
{
    size_t line_size, totalR = 0, chars;

    int ii = 0;
    while (true)
    {
        char line[128];
        if (NULL == fgets(line, 128, file))
            break;

        chars = strlen(line);

        // if (chars == 0) break;
        if (!filename)
        {
            if (chars == 1 && (line[0] == '\n' || line[0] == '\r'))
                break;
            if (chars == 2 && !strcmp(line, "\r\n"))
                break;
        }

        sprintf(buf + totalR, "%s\n", line);
        totalR = strlen(buf);
    }
}

int validateSudokuGrid(void)
{
    char buf[MAX_BUF_SIZE];
    DBG("Reading data");

    if (filename)
    {
        FILE *f = fopen(filename, "r");
        if (!f)
        {
            printf("Unable to open file %s\n", filename);
        }
        readGridFrom(f, buf, MAX_BUF_SIZE);
    }
    else
    {
        printf("No file provided, using stdin...\n");
        printf("Enter each row as one line\nempty line will terminate input\n");
        readGridFrom(stdin, buf, MAX_BUF_SIZE);
    }

    DBGF("Read buf:\n%s\n", buf);

    // TODO: parse grid, and create SudokuGrid object
    Sudoku_Grid *grid = sudoku_grid_create_from_str(buf);

    if (!grid)
    {
        printf("Invalid input :(\ncouldn't parse input\nfor more info use (-v) flag\n");
        exit(1);
    }

    // TODO: Validate grid
    if (!sudoku_grid_is_valid(grid))
    {
        printf("Invalid input :(\nProvided Sudoku Grid is not valid\nNot matching game standards\nfor more info use (-v) flag\n");
        exit(1);
    }

    // TODO: Show result
    char *buff = sudoku_grid_print(grid);

    if (buff)
    {
        printf("Input Sudoku grid is valid!! horaay :)\n");
        printf("Here is parsed board\n%s\n", buff);

        free(buff);
    }
    else
    {
        printf("Invalid input :(\nProvided Sudoku Grid is not valid\nNot matching game standards\nfor more info use (-v) flag\n");
        exit(1);
    }

    DBG("Thank you!");
}

void showArgsMessage(void)
{
    puts("Sudoku grid validator, made by Abed Srour <eng.abdsrour@gmail.com>");
    puts("---------------------------------------------------------------");

    puts("Usage:");
    printf("%s [-h] [-f file] [-v]", appname);
    puts("");
    puts("\t-h\t\t\tHelp: to show this help message!\n");
    puts("\t-f filePath\t\tFile: to read sudoku grid from file");
    puts("\t-v\t\t\tVerbose: to enable verbose mode");
    puts("---------------------------------------------------------------");
}

void parseArgs(int argc, const char **argv)
{
    appname = argv[0];

    if (argc >= 2)
    {
        for (int ii = 1; ii < argc; ii++)
        {
            if (!strncmp("-h", argv[ii], 2))
            { // Help
                showArgsMessage();
                exit(0);
            }
            else if (!strncmp("-f", argv[ii], 2))
            { // File
                if (ii + 1 == argc || argv[ii + 1] == "-")
                {
                    puts("No file input provided!");
                    showArgsMessage();
                    exit(1);
                }
                ii++;
                filename = argv[ii];
            }
            else if (!strncmp("-v", argv[ii], 2))
            { // Verbose
                verboseMode = 1;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    parseArgs(argc, argv);

    DBGF("Args result: appname=%s filename=%s v=%d\n", appname, filename, verboseMode);

    validateSudokuGrid();
    return 0;
}
