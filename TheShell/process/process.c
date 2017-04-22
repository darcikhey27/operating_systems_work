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
