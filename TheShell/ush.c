#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"

#include "./linkedlist/linkedList.h"
#include "./linkedlist/listUtils.h"
#include "./alias/alias.h"
#include "./alias/aliasUtil.h"
#include "./history/history.h"

// linkedlist history counter
int HISTCOUNTER = 0;
void setHistoryCounts(FILE *fin, LinkedList *theList);
void setHistoryCountsDefaults();
void processString(char *string);
FILE* openFile(char *filename);
void checkForAlias(char *string, LinkedList *theList);

void addHistItems(FILE *fin, LinkedList *histList);


// 
int main() {
    FILE *fin = NULL;

    fin = openFile("ushrc");

    LinkedList * aliasList = linkedList();

    if(fin != NULL) {
        //puts("fin is not null");
        setHistoryCounts(fin, aliasList);
    }
    else {
        //puts("fin is null");
        setHistoryCountsDefaults();
    }
    fclose(fin);
    fin = NULL;
    //printf("histcount %d \n", HISTCOUNT);
    //printf("histfilecount %d\n", HISTFILECOUNT);

    puts("printing alias list");
    printList(aliasList, printTypeAlias);


    LinkedList *historyList = linkedList();

    puts("reading ush_history file");
    fin = openFile("ush_history");
    if(fin != NULL) {
        // add the history file elements into the historyList
        addHistItems(fin, historyList);
    }
    fclose(fin);
    puts("printing history list");
    printList(historyList, printTypeHistory);

    /******************** START SHELL HERE ************************/
    // exit program to test history file

    int argc, pipeCount;	
    char **argv = NULL, s[MAX];
    int preCount = 0, postCount = 0;
    char ** prePipe = NULL, ** postPipe = NULL;

    printf("command?: ");
    fgets(s, MAX, stdin);
    strip(s);

    while(strcmp(s, "exit") != 0) {
        // add the command to the history list
        // implement the extra credit here. histitems does not repeat
        addLast(historyList, buildNode_Type_string(s, buildTypeHistory_string));

        // if the user types an alias it will set the alias in the alias
        checkForAlias(s, aliasList);
        
        if(isAlias(s, aliasList) == 0){
            executeAlias(s, aliasList);
            // traverse though the alias list until we find the command that maches 's'
            // then we excecute the tokenized_command with excevp
        }
        

        // this code here will go on the else part of the if above
        pipeCount = containsPipe(s);
        if(pipeCount > 0) {
            prePipe = parsePrePipe(s, &preCount);
            postPipe = parsePostPipe(s, &postCount);
            pipeIt(prePipe, postPipe);
            clean(preCount, prePipe);
            clean(postCount, postPipe);
        }// end if pipeCount	  
        else {
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

    // writeHistoryFile("ush_history");
    // clean stuff here
    clearList(aliasList, cleanTypeAlias);
    free(aliasList);
    aliasList = NULL;
    clearList(historyList, cleanTypeHistory);
    free(historyList);
    historyList = NULL;


    return 0;

}// end main

void checkForAlias(char *line, LinkedList *theList) {
    puts("Checking for aliases");
    char copy[MAX];
    strcpy(copy, line);

    char *isAlias;
    isAlias = strtok(copy, " ");
    strip(isAlias);

    if(strcmp(isAlias, "alias") != 0) {
        // the string is not an alias
        puts("is not alias");
        return;
    }
    puts("is alias");
    // addLast here pass the fin so I can build 
    // the node somewhere else
    printf("the alias that will be passed in is %s\n", line);
    addLast(theList, buildNode_Type_string(line, buildTypeAlias_string));

    // TODO: pass the string instead of the fin pointer


}

FILE* openFile(char *filename) {
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
        fgets(line, MAX, fin);
        checkForAlias(line, theList);
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
void setHistoryCountsDefaults() {

    HISTCOUNT = 100;
    HISTFILECOUNT = 1000;
}


void addHistItems(FILE *fin, LinkedList *histList) {
    puts("in addHistItems");

    char string[MAX];
    int recordsCount = 0;

    fgets(string, MAX, fin);
    while(!feof(fin)) {
        recordsCount++;
        fgets(string, MAX, fin);
    }
    rewind(fin);

    while(recordsCount != 0) {
        // the file may contain aliases and path maybe
        fgets(string, MAX, fin);
        addLast(histList, buildNode_Type_string(string, buildTypeHistory_string));

        puts("in while");
        recordsCount--;
    }
}
