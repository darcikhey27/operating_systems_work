#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alias.h"
#include "aliasUtil.h"
#include "../linkedlist/linkedList.h"
#include "../utils/myUtils.h"
#include "../tokenize/makeArgs.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int isAlias(char *s, LinkedList *theList) {
    if(theList->size == 0) {
        return -1;
    }
    char sCopy[MAX];
    strcpy(sCopy, s);

    Node *curr = theList->head->next;
    Node *prev = theList->head;
    while(curr != NULL) {
        Alias left = *((Alias*) curr);
        if(strcmp(left.alias, s) == 0) {
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }
    return -1;
}

void executeAlias(char *s, LinkedList *theList) {

    char sCopy[MAX];
    strcpy(sCopy, s);

    Node *curr = theList->head->next;
    Node *prev = theList->head;
    while(curr != NULL) {
        Alias left = *((Alias*) curr);
        if(strcmp(left.alias, s) == 0) {
           execvp(left.alias, left.tokenized_command);
           return;
        }
        prev = curr;
        curr = curr->next;
    }
}
