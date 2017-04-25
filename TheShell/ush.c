#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"

#include "./linkedlist/linkedList.h"
#include "./linkedlist/listUtils.h"
#include "./alias/alias.h"
#include "./alias/aliasUtil.h"
#include "./history/history.h"
#include "./history/historyUtil.h"

// linkedlist history counter
//int HISTCOUNTER = 0;

void setHistoryCounts(FILE *fin, LinkedList *theList);
void setHistoryCountsDefaults();
void processString(char *string);
FILE* openFile(char *filename);
void checkForAlias(char *string, LinkedList *theList);
void addHistItems(FILE *fin, LinkedList *histList);
int isChgDir(char *path);
void changeDir(char *s);

int main() {
    FILE *fin = NULL;

    fin = openFile("ushrc");
    LinkedList * aliasList = linkedList();

    if(fin != NULL) {
        //puts("fin is not null");
        setHistoryCounts(fin, aliasList);
        fclose(fin);
        fin = NULL;
    }
    else {
        puts("fin is null");
        setHistoryCountsDefaults();
    }
    //printf("HISTCOUNT %d \n", HISTCOUNT);
    //printf("HISTFILECOUNT %d\n", HISTFILECOUNT);

    //puts("printing alias list");
    //printList(aliasList, printTypeAlias);


    LinkedList *historyList = linkedList();

    //puts("reading ush_history file");
    fin = openFile("ush_history");
    if(fin != NULL) {
        // add the history file elements into the historyList
        addHistItems(fin, historyList);
        fclose(fin);   
        fin = NULL;
    }

    //puts("printing history list");
    //printList(historyList, printTypeHistory);

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

        if(strlen(s) == 0) {
            goto REPROMPT; 
        } 
        
        /* check the tail node.data.command == s dont write repeats to ush_history file
           if(isRepetedCommand(s, historyList) != 0 || isBanBang(s, historyList) != 0) { 
           addLast(historyList, buildNode_Type_string(s, buildTypeHistory_string));
           } 
            */
        // remove this line to test for repeated commands
        addLast(historyList, buildNode_Type_string(s, buildTypeHistory_string));

        // if the user types an alias it will set the alias in the alias
        checkForAlias(s, aliasList);
        //printf("s: %s\n", s);
        // if s is an alias, execute it
        if(isAlias(s, aliasList) == 1){
            //if(displayAliasList(s, aliasList) == 0) displayAliasList(s, aliasList);
           // puts("Executing alias");
            //printf("%s\n", s);
            executeAlias(s, aliasList);
            //puts("done executing alias");
            // traverse though the alias list until we find the command that maches 's'
            // then we excecute the tokenized_command with excevp
        }
        else if(isUnAlias(s) == 1) {
            //puts("removing alias");
            printList(aliasList, printTypeAlias);
            unAliasCommand(s, aliasList);
        }
        else if(isHistoryCommand(s) == 1) {
            //    puts("in else if");
            displayTheHistory(historyList);
        }
        else if(isBangBang(s) == 1) {
            // // add the last command executed by the bang bang
            /*  addLast(historyList, buildNode_Type_string(s, buildTypeHistory_string));
             * this will not work if the bangbang command is an alias like
             * if bangbang command points to ll which is an alias it will not work
             */
            // char *command = excuteBangBang(historyList);
            //addLast(historyList, buildNode_Type_string(command, buildTypeHistory_string));
            executeBangBang(historyList);
        }
        else if(isExecuteHistory(s) == 1) {
            //!513, or !! 
            executeHistNumber(s, historyList); 

            // also add this command to the history list
        }
        else if(isChgDir(s) == 1) {
            changeDir(s);
        }
        //else if(isRedirect(s) == 0) {forkItWithRedirect()}

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
        REPROMPT:
        
        printf("command?: ");
        fgets(s, MAX, stdin);
        strip(s);

    }// end while

    //puts("printing history list --------------");
    //printList(historyList, printTypeHistory);
    // there is not history file "ab+" open for reading and wrting and create the file
    fin = fopen("ush_history", "w");
    writeHistoryFile(fin, historyList);
    fclose(fin);

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
  
    // if they typed the alias command by itselft, display the alias linkedlist
    if(strlen(line) == strlen("alias") && strcmp(line, "alias") == 0) {
        //print alias list
        //puts("printint alias list");
        printList(theList, printTypeAlias);
        return;
    } 
    
    //puts("Checking for aliases");
    char copy[MAX];
    strcpy(copy, line);

    char *isAlias;
    isAlias = strtok(copy, " ");
    strip(isAlias);
   
    if(strcmp(isAlias, "alias") != 0) {
        // the string is not an alias
        //puts("is not alias");
        return;
    }
    //puts("is alias");
    // addLast here pass the fin so I can build 
    // the node somewhere else
    //printf("the alias that will be passed in is %s\n", line);
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
    //char lineCopy[MAX];
    int recordsCount = 0;
    int i;
    // count the number of lines in the file
    fgets(line, MAX, fin);
    while(!feof(fin)) {
        recordsCount++;
        fgets(line, MAX, fin);
    }
    rewind(fin);

    for(i = 0; i < 2; i++) {
        //puts("in for loop");
        fgets(line, MAX, fin);
        processString(line);
        recordsCount--;
    }

    while(recordsCount != 0) {
        // the file may contain aliases and path maybe
        fgets(line, MAX, fin);
        checkForAlias(line, theList);
        //puts("in while");
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
    //puts("in addHistItems");

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

        //puts("in while");
        recordsCount--;
    }
}

int isChgDir(char *path) {
    char *token;
    char copy[MAX];
    strcpy(copy, path);

    token = strtok(copy, " ");
    if(strcmp(token, "cd") == 0) {
        return 1;
    }
    return 0;
}


void changeDir(char *s) {
    char *token;
    char path[MAX];
    char copy[MAX];
    strcpy(copy, s);

    token = strtok(copy, " ");
    token = strtok(NULL, " ");
    strcpy(path, token);

    chdir(path);
}
