#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "alias.h"
#include "../linkedlist/linkedList.h"
//#include "actor.h"

void cleanTypeAlias(void * ptr) {
    if(ptr == NULL) {
        puts("from cleanTypeAlias ptr is null");
        exit(-99);
    }
    Alias *alias = (Alias*) ptr;
    free(alias->alias);

    clean(alias->argc, alias->tokenized_command);
    alias->tokenized_command = NULL;

    free(alias);
}

void* buildTypeAlias(FILE *fin) {
    if(fin == NULL) {
        puts("fin is null");
        exit(-99);
    }

    return NULL;
}

void printTypeAlias(void* passedIn) {

    Alias alias = *((Alias*) passedIn);
    printf("alias %s='", alias.alias);

    printargs(alias.argc, alias.tokenized_command); 

}
void *buildTypeAlias_string(char* string) {
    char stringCopy[MAX];
    strcpy(stringCopy, string);

    char *left;
    char *right;

    left = strtok(stringCopy, "=");
    right = strtok(NULL, "=");
    strtok(left, " ");

    left = strtok(NULL, " ");
    right = strtok(right, "'");

    //printf("left: %s right: %s\n", left, right);
    // allocate memory for the alias object here 
    Alias *aliasObject = (Alias*) malloc(sizeof(Alias));
    aliasObject->alias = (char*) malloc(sizeof(left) + 1);

    strcpy(aliasObject->alias, left);
    aliasObject->argc = makeArgs(right, &(aliasObject->tokenized_command));

    return aliasObject; // create alias object and return it
}
void * buildTypeAlias_Prompt(FILE * fin) {

    return NULL;
}

int compareAlias(const void * p1, const void * p2) {

    if(p1 == NULL || p2 == NULL) {
        puts("p1 or p2 is NULL");
        exit(-99);
    }
    Alias left = *((Alias*) p1);
    Alias right = *((Alias*) p2);

    if(strcmp(left.alias, right.alias) > 0) {
        return 1;
    }
    else if(strcmp(left.alias, right.alias) < 0) {
        return -1;
    }
    else {
        return 0;
    }
    return 0;
}

