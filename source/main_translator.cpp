#include <stdio.h>
#include <stdlib.h>
#include "translator.h"

int main(int argc, const char *argv[])
{
    const char *fileInName  = NULL;
    char       *fileOutName = NULL;

    if (argc == 1)
    {
        printf("ERROR: file name not given\n");
        return 0;
    }

    processArgv(argc, argv, &fileInName, &fileOutName);

    FILE *fin  = fopen (fileInName,  "rb");
    if (!fin)  { perror(fileInName); return 0; }

    int   *bufIn   = NULL;
    size_t bufSize = 0;

    int error = loadProgramBin(&bufIn, &bufSize, fin);
    if (error) { printf("ERROR: %d\n", error); return error; }

    FILE *fNasmOut = fopen (fileOutName, "w");
    if (!fNasmOut) { perror(fileInName); return 0; }

    error = runDisassembler(bufIn, fNasmOut);
    if (error)
    {
        printf("ERROR: %d\n", error);
        return error;
    }

    free(bufIn);
}
