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
void setHistoryCounts(FILE *fin, LinkedList *theList);
void setHistoryCountsDefaults();
void processString(char *string);
FILE* openUshrcFile(char *filename);
void checkForAlias(FILE *fin, LinkedList *theList);

// 
int main()
{

    FILE *fin = NULL;

    fin = openUshrcFile("ushrc");

    LinkedList * aliasList = linkedList();

    if(fin != NULL) {
        //puts("fin is not null");
        setHistoryCounts(fin, aliasList);
    }
    else {
        //puts("fin is null");
        setHistoryCountsDefaults();
    }
    printf("histcount %d \n", HISTCOUNT);
    printf("histfilecount %d\n", HISTFILECOUNT);
    puts("here");




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

void setHistoryCounts(FILE *fin, LinkedList *theList) {
    char line[MAX];
    char lineCopy[MAX];
    int recordsCount = 0;
    int i;

    fgets(line, MAX, fin);
    while(!feof(fin)) {
        recordsCount++;
        fgets(line, MAX, fin);
    }
    rewind(fin);
    
    for(i = 0; i < 2; i++) {
        puts("in for loop");
        fgets(line, MAX, fin);
        processString(line);
        recordsCount--;
    }
    
    while(recordsCount != 0) {
        // the file may contain aliases and path maybe
        checkForAlias(fin, theList);
        puts("in while");
        recordsCount--;
    }
    /*
       fgets(line, MAX, fin);
       while(!feof(fin)) {
       checkForAlias(line, theList);
       fgets(line, MAX, fin);
       }
       rewind(fin); */
}
void checkForAlias(FILE *fin, LinkedList *theList) {
    puts("Checking for aliases");
    char string[MAX];
    fgets(string, MAX, fin);
    strip(string);
    char copy[MAX];
    strcpy(copy, string);
    char *isAlias;
    isAlias = strtok(copy, " ");
    strip(isAlias);

    if(strcmp(isAlias, "alias") != 0) {
        // the string is not an alias
        return;
    }
    // addLast here pass the fin so I can build 
    // the node somewhere else
    
    /*
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
    // addFirst(theList, )
    */
    addLast(theList, buildNode(fin, buildTypeAlias));
    //printList(theList); need to pass convertData


}
void setHistoryCountsDefaults() {

    HISTCOUNT = 100;
    HISTFILECOUNT = 1000;
}
