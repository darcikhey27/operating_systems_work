#ifndef PROCESS_H
#define PROCESS_H

void forkIt(char ** argv);

void forkItWithRedirect(char **left, char** right);

#endif
