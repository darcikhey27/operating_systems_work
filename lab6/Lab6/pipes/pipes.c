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
  
    //printf("s is %s\n", s);
    // read the string until we see a pipe
    int stringlen = strlen(s);

    char *token;
    char line[MAX];
    strcpy(line, s);
    token = strtok(line, "|");
    strip(token);
    //printf("token is %s\n", token);
    
    char **argv = NULL;
    int argc = 0;
    
    argc = makeArgs(token, &argv);

    printargs(argc, argv);
    *preCount = argc;
    
    return argv;
}

char** parsePostPipe(char *s, int *postCount) {
   
    //printf("s = %s\n", s);

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

    printargs(argc, argv);
    
    return argv;
}

void pipeIt(char ** prePipe, char ** postPipe) {

    // take the two commands and work it
	pid_t pid;
	int fd[2], res, status;
	res = pipe(fd);

	if(res < 0) {
		printf("Pipe Failure\n");
		exit(-1);
	}
	pid = fork();

	if(pid != 0) {
        close(fd[1]);
        close(0);
        dup(fd[0]);
        close(fd[0]);

        //execlp("wc", "wc", "-w", NULL);
        execvp(postPipe[0], postPipe);
	} 
    else {
		close(fd[0]);
		close(1);
		dup(fd[1]);
		close(fd[1]);
		//execlp("ls", "ls", "-l", NULL);
        execvp(prePipe[0], prePipe);
	}
}
