#include "fileUtil.h"

FILE * openInputFile_Args(int argc, char * args[])
{
    return NULL;
}

int countRecords(FILE * fin, int linesPerRecord)
{
    return 1;
}



void displayFileContents(int num, FILE * fin)
{

}

void readFileName(char * filename)
{

}

FILE * openInputFile_String(char * fn)
{
    return NULL;
}

void displayFile_FilePointer(FILE * fin)
{

}

// work on this method first
FILE * openOutputFile_FileName(char * fn) {

    return NULL;
}

void displayFile_OutputFile(FILE * fin, FILE * fout)
{

}

// this is the first method we need
FILE * openInputFile_Prompt() {
    puts("in openInputFile_Prompt()") 
    FILE *fin = NULL; 
    char fileName[MAX];
    while(1) {
        printf("Ente the name of the file: ");
        scanf("%s", fileName);

        fin = fopen(fileName, "r");

        if(fin == NULL) {
            puts("fin is null, enter a good file name");
            continue;
        }
        break;
    }
    return fin;
}

FILE * openOutputFile_Prompt()
{
    return NULL;
}

