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
    puts("Sudoku grid Generator, made by Abed Srour <eng.abdsrour@gmail.com>");
    puts("---------------------------------------------------------------");
    
    puts("Usage:");
    printf("%s [-h] [-f file] [-v]", appname);
    puts("");
    puts("\t-h\tHelp: to show this help message!\n");
    puts("\t-f file\tFile: to write sudoku grid into file");
    puts("\t\tIf no file provided stdout will be used");
    puts("\t-v\tVerbose: to enable verbose mode");
    puts("---------------------------------------------------------------");
}

void parseArgs(int argc, const char **argv) {
    appname = argv[0];

    // TODO: parse args
    if ( argc > 2 ) {
        for ( int ii = 1; ii < argc; ii++ ) {
            if (!strncmp("-h", argv[ii], 2)) { // Help
                showArgsMessage();
                exit(0);
            } else if (!strncmp("-f", argv[ii], 2)) {
                if (ii == argc || argv[ii+1] == "-") {
                    puts("No file input provided!");
                    showArgsMessage();
                    exit(1);
                }
                ii ++;
                filename = argv[ii];
            } else if (!strncmp("-v", argv[ii], 2)) {
                verboseMode = 1;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    parseArgs(argc, argv);

    printf("appname=%s filename=%s v=%d", appname, filename, verboseMode);
    return 0;
}
