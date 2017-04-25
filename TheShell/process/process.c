#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "process.h"

void forkIt(char ** argv) {

    pid_t pid = fork();

    int status = 0;

    if(pid != 0) {
        waitpid(pid, &status, 0);
    }
    else {
        execvp(argv[0], argv);
        exit(-1);
    }
}

void forkItWithRedirect(char **preRedirect, char** postRedirect) {
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
            execvp(postRedirect[0], postRedirect);
            exit(-1);
        } 
        else {
            close(fd[0]);
            close(1);
            dup(fd[1]);
            close(fd[1]);
            execvp(preRedirect[0], preRedirect);
            exit(-1);
        }
    }
}

/*
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
*/
