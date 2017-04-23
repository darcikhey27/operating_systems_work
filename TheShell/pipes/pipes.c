#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../utils/myUtils.h"
#include "../tokenize/makeArgs.h"
#include "pipes.h"

/* checks and counts how many pipes are in the s string */
int containsPipe(char *s) {
    int stringlen = strlen(s);
    int i;
    int pipeCount = 0;

    for(i = 0; i < stringlen; i++ ) {
        if(s[i] == '|') {
            pipeCount++;
        }
    }
    //printf("Pipe count is %d\n", pipeCount);
    return pipeCount;
}

/* saves the string until we see a pipe */
char** parsePrePipe(char *s, int* preCount) {

    //printf("in parsePrePipe()\n");
    // read the string until we see a pipe
    //int stringlen = strlen(s);

    char *token;
    char line[MAX];
    strcpy(line, s);
    token = strtok(line, "|");
    strip(token);
    //printf("token is %s\n", token);

    char **argv = NULL;
    int argc = 0;

    argc = makeArgs(token, &argv);

    //printargs(argc, argv);
    *preCount = argc;

    return argv;
}

/* parses a string until after the pipe */
char** parsePostPipe(char *s, int *postCount) {
    //printf("In parsePostPipe\n");

    char *token;
    char line[MAX];
    strcpy(line, s);
    token = strtok(line, "|");
    token = strtok(NULL, "|");
    strip(token);
    //printf("token is %s\n", token);

    char **argv = NULL;
    int argc = 0;

    argc = makeArgs(token, &argv);

    //printargs(argc, argv);
    *postCount = argc;

    return argv;
}

/* exectutes both of the strings, left and right */
void pipeIt(char ** prePipe, char ** postPipe) {

    // take the two commands and work it
    //printf("In pipeIt()\n");
    pid_t pid;
    int fd[2], res, status;
    res = pipe(fd);

    if(res < 0) {
        printf("Pipe Failure\n");
        exit(-1);
    }
    pid = fork();
    status = 0;

    if(pid != 0) {
        waitpid(pid, &status, 0);
    } 
    else {
        //execlp("ls", "ls", "-l", NULL);
        pipe(fd);
        pid = fork();
        if(pid != 0) {
            close(fd[1]);
            close(0);
            dup(fd[0]);
            close(fd[0]);

            //execlp("wc", "wc", "-w", NULL);
            execvp(postPipe[0], postPipe);
            exit(-1);
        } 
        else {
            close(fd[0]);
            close(1);
            dup(fd[1]);
            close(fd[1]);
            execvp(prePipe[0], prePipe);
            exit(-1);
        }
    }
}
