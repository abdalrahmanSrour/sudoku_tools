#include "../inc/SudokuGrid.h"

unsigned char verboseMode = 0;
const char *filename = NULL;
const char *appname = NULL;

int generateSudokuGrid(void)
{
    Sudoku_Grid *grid = sudoku_grid_create();

    DBG("Generate grid");
    if (sudoku_grid_generate(grid))
    {
        printf("Couldn't generate sudoku grid! :(\n");
        exit(1);
    }
    else
    {
        printf("Sudoku grid generated successfuly! horaay :)\n");
    }
    
    
    char *buf = sudoku_grid_print(grid);

    if (!buf)
    {
        printf("Couldn't generate sudoku grid! :(\n");
        exit(1);
    }

    DBGF("Sudoku grid generated successfuly!\n----\n%s\n----\n", buf);

    if (filename)
    {
        printf("Write to file > %s\n", filename);
        FILE *f = fopen(filename, "wb+");
        if (!f)
        {
            printf("Can't open file!\n");
            exit(1);
        }
        fprintf(f, "Generated using SudokuGenerator, created by Abed Srour <eng.abdsrour@gmail.com>\n%s\n", buf);
        fclose(f);
    }
}

void showArgsMessage(void)
{
    puts("Sudoku grid generator, made by Abed Srour <eng.abdsrour@gmail.com>");
    puts("---------------------------------------------------------------");
    puts("Usage:");
    printf("%s [-h] [-f file] [-v]", appname);
    puts("");
    puts("\t-h\t\t\tHelp: to show this help message!\n");
    puts("\t-f filePath\t\tFile: to write sudoku grid to file");
    puts("\t\t\t\tOtherwise stdout will be used to show grid");
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

    DBGF("appname=%s filename=%s v=%d\n", appname, filename, verboseMode);

    generateSudokuGrid();
    return 0;
}
