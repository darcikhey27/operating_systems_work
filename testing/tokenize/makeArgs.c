#include "makeArgs.h"
// Darci K SAucedo
//

void clean(int argc, char **argv) {
    int i;
    puts("cleaning");
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

int makeArgs(char *s, char *** argv) {
    int count = 0;
    int i;
    char *tempToken;
    char *token;
    char line[MAX];
    strcpy(line, s);
    char copy[MAX];

    tempToken = strtok(s, " ");
    while(tempToken != NULL) {
        count++;
        tempToken = strtok(NULL, " ");
    }
    if(count <= 0) {
        return -1;
    }
    // allocate memory for the array
    *argv = (char**) calloc(count + 1, sizeof(char*));

    token = strtok(line, " ");
    strcpy(copy, token);
    for(i = 0; i < count; i++) {
        // allocate mem for one element of the array
        (*argv)[i]  = calloc(strlen(copy)+1, sizeof(char));
        strcpy((*argv)[i], copy);
        token = strtok(NULL, " ");

        if(token != NULL) {
            strcpy(copy, token);
        }
    }
    return count;

}// end makeArgs
