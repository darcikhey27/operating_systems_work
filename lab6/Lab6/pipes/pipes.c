#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../utils/myUtils.h"
#include "../tokenize/makeArgs.h"


#include "pipes.h"
/* containsPipe – In this function print out the count of the number of pipes in the string */
int containsPipe(char *s) {
    
    int stringlen = strlen(s);
    int i;
    int pipeCount = 0;

    for(i = 0; i < stringlen; i++ ) {
        if(s[i] == '|') {
            pipeCount++;
        }
    }
    printf("pipe count is %d\n", pipeCount);
    return pipeCount;
}

char** parsePrePipe(char *s, int* preCount) {
  
    printf("s is %s\n", s);
    // read the string until we see a pipe
    int stringlen = strlen(s);
    int i;
    int foundPipeAt = 0;
    char preString[MAX];
    
    for(i = 0; i < stringlen; i++) {
        if(s[i] != '|') {
            //preString[i] == s[i];
            printf("s[%d] %c\n", i, s[i]);
        } 
    }
    //strip(preString);
    //printf("prestring is %s\n", preString);
    
    char **argv = NULL;
    int argc = 0;
    
    //argc = makeArgs(preString, &argv);

    //printargs(argc, argv);
    
    return argv;
}

char** parsePostPipe(char *s, int *postCount) {
    
    int stringlen = strlen(s);
    int i;
    int foundPipeAt = 0;
    char right[MAX];

    for(i = 0; i < stringlen; i++) {
        if(s[i] != '|') {
            foundPipeAt++;
        }
    }
    for(i = foundPipeAt; i < stringlen; i++) {
        right[i] = s[i];
    }
    strip(right);
    puts(right);

    char **argv = NULL;
    int argc = 0;
    
    argc = makeArgs(right, &argv);
    printargs(argc, argv);
    *postCount = argc;
    printf("postcount %d\n", *postCount);
    return argv;
}

void pipeIt(char ** prePipe, char ** postPipe) {

    // take the two commands and work it
    puts("about to pipe");
}
