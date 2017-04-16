// Darci K SAucedo
//

#include "lab4.h"

void clean(int argc, char **argv) {
    int i;

    for(i = 0; i < argc; i++) {
        free(argv[i]);
    }
    free(argv);
}// end clean

void printargs(int argc, char **argv)
{
    int x;
    for(x = 0; x < argc; x++)
        printf("%s\n", argv[x]);

}// end printargs

int makeargs(char *s, char *** argv) {
    int count = 0;
    int i;
    char *tempToken;
    char *token;
    char line[MAX];
    strcpy(line, s);
    char copy[MAX];

    tempToken = strtok_r(s, " ", &s);
    while(tempToken != NULL) {
        count++;
        tempToken = strtok_r(NULL, " ", &s);
    }
    if(count <= 0) {
        return -1;
    }
    // allocate memory for the array
    *argv = (char**) calloc(count + 1, sizeof(char*));

    char* new = line;
    token = strtok_r(line, " ", &new);
    strcpy(copy, token);
    for(i = 0; i < count; i++) {
        // allocate mem for one element of the array
        (*argv)[i]  = calloc(strlen(copy)+1, sizeof(char));
        strcpy((*argv)[i], copy);
        token = strtok_r(NULL, " ", &new);

        if(token != NULL) {
            strcpy(copy, token);
        }
    }
    return count;

}// end makeArgs  





