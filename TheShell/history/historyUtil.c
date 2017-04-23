#include "historyUtil.h"
#include "history.h"
#include <stdlib.h>
#include <stdio.h>
#include "../linkedlist/linkedList.h"
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

    if(theList->size < HISTCOUNT) {
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
        for(i = 0;  i < (theList->size - HISTCOUNT); i++) {
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

}

