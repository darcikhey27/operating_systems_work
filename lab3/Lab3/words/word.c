#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"
#include "../utils/myUtils.h"

void cleanTypeWord(void * ptr) {
   
    if(ptr == NULL) {
        puts("ptr is null");
        exit(-99);
    }
    Word *word = (Word*) ptr;
    free(word->ltrs);
    free(word);
    word = NULL;
}

void* buildTypeWord(FILE *fin) {

    if(fin == NULL) {
        puts("fin is null");
        exit(-99);
    }
    // buildNode gets called from buildTypeWord
    // 
    char readWord[256];
    char temp[10];

    Word *word = (Word*) malloc(sizeof(Word));

    fgets(readWord, 256, fin);
    strip(readWord);

    word->ltrs = (char*) malloc(strlen(readWord)+1);
    strcpy(word->ltrs, readWord);
    int len = strlen(readWord);
    word->len = len;

    // get rid of carriage return
    //fgets(temp, 10, fin);
    return word;
    
}

void printTypeWord(void* passedIn) {
    Word word =  *((Word*) passedIn);
    printf("word: %s len: %i\n", word.ltrs, word.len);
}

void * buildTypeWord_Prompt(FILE * fin) {
    char temp[MAX];
    int len = 0;

    printf("Enter word: ");
    fgets(temp, MAX, fin);
    strip(temp);
    
    len = strlen(temp);
    Word *word = (Word*) malloc(sizeof(Word));
    word->ltrs = (char*) malloc(len+1);
    strcpy(word->ltrs, temp);
    word->len = len;

    return word;

}

int compareWord(const void * p1, const void * p2) {
    if(p1 == NULL || p2 == NULL) {
        puts("p1 or p2 is NULL");
        exit(-99);
    }

    Word left = *((Word*)p1);
    Word right = *((Word*)p2);

    return strcmp(left.ltrs, right.ltrs);
}

