
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
    //puts("in isAlias");
    if(theList->size == 0) {
        //puts("theList size is 0");
        return -1;
    }
    //puts("checking for");
    char sCopy[MAX];
    strcpy(sCopy, s);

    Node *curr = theList->head->next;
    //Node *prev = theList->head;
    while(curr != theList->head) {
        Alias alias = *((Alias*) curr->data);
        //printf("left.alias %s\n", alias.alias);

        if(strcmp(alias.alias, s) == 0) {
           // puts("match was found");
            return 1;
        }
        //   prev = curr;
        curr = curr->next;
    }
    return 0;
}

void executeAlias(char *s, LinkedList *theList) {

    char sCopy[MAX];
    strcpy(sCopy, s);

    Node *curr = theList->head->next;
    //Node *prev = theList->head;
    while(curr != theList->head) {
        Alias left = *((Alias*) curr->data);
        if(strcmp(left.alias, s) == 0) {
            //puts("executing alias in if");
            // add this command to the alias linkedlist
            //
            //execvp(left.tokenized_command[0], 
            //        left.tokenized_command);
            forkIt(left.tokenized_command);
            return;
        }
        // prev = curr;
        curr = curr->next;
    }
}

int isUnAlias(char *s) {
    //printf("s is %s\n", s);
    char copy[MAX];
    strcpy(copy, s);
    char *token;

    // unalias ll
    token = strtok(copy, " ");
    //printf("token is %s\n", token);
    strip(token);
    if(strcmp(token, "unalias") == 0) {
       // puts("match was found");
        return 1;
    }
    //puts("match was not found");
    return 0;
}


void unAliasCommand(char *s, LinkedList *theList) {
    if(s == NULL || theList == NULL) {
        puts("s is null or theList is null");
        exit(-1);
    }

    char copy[MAX];
    strcpy(copy, s);
    char *token;

    // unalias ll
    token = strtok(copy, " ");
    token = strtok(NULL, " ");
    
    Node *curr = theList->head->next;
    Node *prev = theList->head;
    while(curr != theList->head) {

        Alias item = *((Alias*) curr->data);

        if(strcmp(item.alias, token) == 0) {
            printf("alias %s was removed \n", token);
            prev->next = curr->next;
            cleanTypeAlias(curr->data);
            prev->next = curr->next;
            curr->next->prev = prev;

            free(curr);
            theList->size--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }

}


