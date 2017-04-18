#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


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
    return pipeCount;
}

char** parsePrePipe(char *s, int* preCount) {
    
    return NULL;
}

char** parsePostPipe(char *s, int *postCount) {

    return NULL;
}
