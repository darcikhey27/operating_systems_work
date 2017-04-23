#include "historyUtil.h"
#include "history.h"
#include <stdlib.h>
#include <stdio.h>
#include "../linkedlist/linkedList.h"
// historyUtil.c

void writeHistoryFile(FILE *fin, LinkedList *theList) {

    //puts("about to add to history list");
    Node *curr = theList->head->next;
    while(curr != NULL) {
        
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

void displayTheHistory(int count, LinkedList *theList) {
    
    


}
