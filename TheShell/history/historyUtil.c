#include "historyUtil.h"
#include "history.h"
#include <stdlib.h>
#include <stdio.h>
#include "../linkedlist/linkedList.h"
#include "../process/process.h"
// historyUtil.c

void writeHistoryFile(FILE *fin, LinkedList *theList) {

    //puts("about to add to history list");
    Node *curr = theList->head->next;
    while(curr != theList->head) {

        History left = *((History*) curr->data);
        //printf("writing this %s to file\n", left.command);
        fprintf(fin, "%s\n", left.command); 

        curr = curr->next;
    }
}

int isHistoryCommand(char *s) {
    if(strcmp(s, "history") == 0) {
        puts("you typed history");
        return 1;
    }
    return 0;
}

void displayTheHistory(LinkedList *theList) {
    if(theList == NULL) {
        printf("The list is null displayTheHistory()\n");
        exit(-99);
    } 

    Node *curr;

    int count;

    if(theList->size < HISTCOUNT) { // && HISTCONT < HISTFILECOUNT
        // display all the nodes
        curr = theList->head->next;
        count = 1;
        while(curr != theList->head) {

            History historyItem = *((History*) curr->data);
            printf("%d  %s\n", count, historyItem.command);

            curr = curr->next;
            count++;
        }     
    }
    else {

        int i;
        curr = theList->head->next;
        count = 1;
        int stop = (theList->size - HISTCOUNT);
        printf("stop %d\n", stop);

        for(i = 0;  i < stop; i++) {
            curr =curr->next;
            count++;
        }

        // only display elements from the tail of the list to stop pointer
        while(curr != theList->head) {
            History historyItem = *((History*) curr->data);
            printf("%d  %s\n", count, historyItem.command);

            count++;
            curr = curr->next;
        }
    }
}


int isExecuteHistory(char *s) {
    char copy[MAX];
    strcpy(copy, s);

    if(copy[0] == '!') {
        puts("is !x command");
        return 1;
    }
    return 0;
}

void executeHistNumber(char *s, LinkedList *theList) {
    char copy[MAX];
    strcpy(copy, s);
    char* token;
    int commandNumber;

    token = strtok(copy, "!");
    printf("token is %s\n", token);
    strip(token); 
    commandNumber = atoi(token);
    printf("commandnumber is %d\n", commandNumber);

    Node *tail = theList->head->prev;
    int index = theList->size;

    while(tail != theList->head) {
        if(index == commandNumber) {
            History historyItem = *((History*)tail->data);
            printf("executing %d%s\n", commandNumber, historyItem.command);
            forkIt(historyItem.tokenized_command);
            return;
        }
        tail = tail->prev;
        index--;
    }
}

int isBangBang(char *s) {
    printf("%s\n", s);
    char copy[MAX];
    strcpy(copy, s);

    if(strcmp(copy, "!!") == 0 && strlen(copy) == 2) {
        puts("is bang bang");
        return 1;
    }
    return 0;
}


void executeBangBang(LinkedList *theList) {
    if(theList == NULL) {
        puts("The list is null bangbang()");
        exit(-99);
    }
    Node *tail = theList->head->prev;
    tail = tail->prev;
    History historyItem = *((History*)tail->data);
    printf("%s\n", historyItem.command);
    forkIt(historyItem.tokenized_command);
    return;
}

