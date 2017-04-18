#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../utils/myUtils.h"


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
   
    // read the string until we see a pipe
    int stringlen = strlen(s);
    int i;
    int foundPipeAt = 0;
    char preString[MAX];
    
    for(i = 0; i < stringlen; i++) {
        if(s[i] != '|') {
            preString[i] == s[i];
        } 
    }



    //makeArgs(preString)
    
    return NULL;
}

char** parsePostPipe(char *s, int *postCount) {

    return NULL;
}
