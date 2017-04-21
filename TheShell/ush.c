#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"

#include "./linkedlist/linkedList.h"
#include "./linkedlist/listUtils.h"
#include "./alias/alias.h"
#include "./history/history.h"

// linkedlist history counter
int histCounter = 0;
void setHistoryCounts(FILE *fin);
void setHistoryCountsDefaults();
void setHistoryCountsDefaults();
void processString(char *string);
FILE* openUshrcFile(char *filename);
void checkForAlias(char *string);

// 
int main()
{

    FILE *fin = NULL;

    fin = openUshrcFile("ushrc");

    if(fin != NULL) {
        //puts("fin is not null");
        setHistoryCounts(fin);
    }
    else {
        //puts("fin is null");
        setHistoryCountsDefaults();
    }
    printf("histcount %d \n", HISTCOUNT);
    printf("histfilecount %d\n", HISTFILECOUNT);
    puts("here");
    // readUsh_historyFile();


    // exit program to test history file


    /*
       int argc, pipeCount;	
       char **argv = NULL, s[MAX];
       int preCount = 0, postCount = 0;
       char ** prePipe = NULL, ** postPipe = NULL;

       printf("command?: ");
       fgets(s, MAX, stdin);
       strip(s);

       while(strcmp(s, "exit") != 0)
       {
       pipeCount = containsPipe(s);
       if(pipeCount > 0)
       {
       prePipe = parsePrePipe(s, &preCount);
       postPipe = parsePostPipe(s, &postCount);
       pipeIt(prePipe, postPipe);
       clean(preCount, prePipe);
       clean(postCount, postPipe);
       }// end if pipeCount	  

       else
       {
       argc = makeArgs(s, &argv);
       if(argc != -1)
       forkIt(argv);

       clean(argc, argv);
       argv = NULL;
       }

       printf("command?: ");
       fgets(s, MAX, stdin);
       strip(s);

       }// end while

*/
    return 0;

}// end main

FILE* openUshrcFile(char *filename) {
    FILE *fin = NULL;
    fin = fopen(filename, "r");

    return fin;
}
void processString(char *string) {
    char *token;
    char copy[MAX];
    strcpy(copy, string);

    token = strtok(copy, "=");
    if(strcmp(token, "HISTCOUNT") == 0) {
        token = strtok(NULL, "=");
        HISTCOUNT = atoi(token);
    }
    else if(strcmp(token, "HISTFILECOUNT") == 0) {
        token = strtok(NULL, "=");
        HISTFILECOUNT = atoi(token);
    }
}

void setHistoryCounts(FILE *fin) {
    char line[MAX];
    char lineCopy[MAX];
    int counter = 0;
    int i;

    fgets(line, MAX, fin);
    while(!feof(fin)) {
        processString(line);
        counter++;
        fgets(line, MAX, fin);

        if(counter > 2) {
            checkForAlias(line);
        }
    }
    rewind(fin);
}
void checkForAlias(char *string) {
    puts("Checking for aliases");
    char stringCopy[MAX];
    strcpy(stringCopy, string);
    char *left;
    char *right;
    
    left = strtok(stringCopy, "=");
    right = strtok(NULL, "=");
    strtok(left, " ");

    left = strtok(NULL, " ");
    right = strtok(right, "'");

    printf("left: %s right: %s\n", left, right);

    // add the alias to the alias file? 

    
}
void setHistoryCountsDefaults() {

    HISTCOUNT = 100;
    HISTFILECOUNT = 1000;
}
