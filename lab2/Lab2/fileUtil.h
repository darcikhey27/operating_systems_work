#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

FILE * openInputFile_Args(int argc, char * args[]);
int countRecords(FILE * fin, int linesPerRecord);
void displayFileContents(int num, FILE * fin);

void readFileName(char []);
FILE * openInputFile_String(char * fn);
void displayFile_FilePointer(FILE * fin);

FILE * openInputFile_Prompt();
FILE * openOutputFile_FileName(char * fn);
void displayFile_OutputFile(FILE * fin, FILE * fout);

FILE * openOutputFile_Prompt();


#endif // FILEUTIL_H

