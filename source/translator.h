#ifndef  __DISASSEMBLER_H__
#define  __DISASSEMBLER_H__

const int CommandVersion = 5;

int processArgv(int argC, const char *argV[], const char **fileInName, char **fileOutName);

int loadProgramBin(int **bufIn, size_t *bufSize, FILE *fin);

int runDisassembler(int *bufIn, FILE *fout);

#endif //__DISASSEMBLER_H__
