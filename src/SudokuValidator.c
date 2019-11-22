#include "../inc/SudokuGrid.h"

unsigned char verboseMode = 0;
const char *filename = NULL;
const char *appname = NULL;

int validateSudokuGrid(int isFile, char *filename)
{
    // TODO: read file content, or read from stdin

    // TODO: parse grid, and create SudokuGrid object

    // TODO: Validate grid

    // TODO: Show result
}

void showArgsMessage()
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

    if ( argc >= 2 ) {
        for ( int ii = 1; ii < argc; ii++ ) {
            if (!strncmp("-h", argv[ii], 2)) { // Help
                showArgsMessage();
                exit(0);
            } else if (!strncmp("-f", argv[ii], 2)) { // File
                if (ii + 1 == argc || argv[ii+1] == "-") {
                    puts("No file input provided!");
                    showArgsMessage();
                    exit(1);
                }
                ii ++;
                filename = argv[ii];
            } else if (!strncmp("-v", argv[ii], 2)) { // Verbose
                verboseMode = 1;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    parseArgs(argc, argv);

    DBGf("Args result: appname=%s filename=%s v=%d", appname, filename, verboseMode);


    return 0;
}
