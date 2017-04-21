#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"
#include "../utils/myUtils.h"

void cleanTypeCommand(void * ptr) {
   
    // if(ptr == NULL) {
    //     puts("ptr is null");
    //     exit(-99);
    // }
    // Command *commnad = (Command*) ptr;
    // free(commnad->ltrs);
    // free(commnad);
    // commnad = NULL;
}

void* buildTypeCommand(FILE *fin) {

    // if(fin == NULL) {
    //     puts("fin is null");
    //     exit(-99);
    // }
    // // buildNode gets called from buildTypeCommand
    // // 
    // char readCommand[256];
    // char temp[10];

    // Command *commnad = (Command*) malloc(sizeof(Command));

    // fgets(readCommand, 256, fin);
    // strip(readCommand);

    // commnad->ltrs = (char*) malloc(strlen(readCommand)+1);
    // strcpy(commnad->ltrs, readCommand);
    // int len = strlen(readCommand);
    // commnad->len = len;

    // // get rid of carriage return
    // //fgets(temp, 10, fin);
    // return commnad;
    
}

void printTypeCommand(void* passedIn) {
    // Command commnad =  *((Command*) passedIn);
    // printf("commnad: %s len: %i\n", commnad.ltrs, commnad.len);
}

void * buildTypeCommand_Prompt(FILE * fin) {
    // char temp[MAX];
    // int len = 0;

    // printf("Enter commnad: ");
    // fgets(temp, MAX, fin);
    // strip(temp);
    
    // len = strlen(temp);
    // Command *commnad = (Command*) malloc(sizeof(Command));
    // commnad->ltrs = (char*) malloc(len+1);
    // strcpy(commnad->ltrs, temp);
    // commnad->len = len;

    // return commnad;

}

int compareCommand(const void * p1, const void * p2) {
    // if(p1 == NULL || p2 == NULL) {
    //     puts("p1 or p2 is NULL");
    //     exit(-99);
    // }

    // Command left = *((Command*)p1);
    // Command right = *((Command*)p2);

    // return strcmp(left.ltrs, right.ltrs);
}

