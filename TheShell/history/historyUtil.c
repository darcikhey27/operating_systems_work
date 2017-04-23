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

    Node *curr = theList->head->next;

    int displayCount = HISTCOUNT;
    int count = 1;
    if(theList->size < displayCount) {
        // display all the nodes
        while(curr != theList->head) {

            History historyItem = *((History*) curr->data);
            printf("%d  %s\n", count, historyItem.command);

            curr = curr->next;
            count++;
        }     
    }
}

