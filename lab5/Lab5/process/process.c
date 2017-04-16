#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "process.h"

void forkIt(char ** argv) {
    // execute the commands in teh 2d array argv
    
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
