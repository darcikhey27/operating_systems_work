#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alias.h"
#include "aliasUtil.h"
#include "../process/process.h"
#include "../linkedlist/linkedList.h"
#include "../utils/myUtils.h"
#include "../tokenize/makeArgs.h"


int isAlias(char *s, LinkedList *theList) {
    puts("in isAlias");
    if(theList->size == 0) {
        puts("theList size is 0");
        return -1;
    }
    puts("checking for");
    char sCopy[MAX];
    strcpy(sCopy, s);

    Node *curr = theList->head->next;
    Node *prev = theList->head;
    while(curr != NULL) {
        Alias alias = *((Alias*) curr->data);
        printf("left.alias %s\n", alias.alias);
        
        if(strcmp(alias.alias, s) == 0) {
            puts("match was found");
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
        Alias left = *((Alias*) curr->data);
        if(strcmp(left.alias, s) == 0) {
            puts("executing alias in if");
           //execvp(left.tokenized_command[0], 
           //        left.tokenized_command);
           forkIt(left.tokenized_command);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}
