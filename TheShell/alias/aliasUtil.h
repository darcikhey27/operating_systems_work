#ifndef ALIASUTIL_H_
#define ALIASUTIL_H_
#include "../linkedlist/linkedList.h"

/* will traverse the alias linkedlist, if it
 * finds a match of s it will execute the 
 * tokenized command with execvp(...)
 */
int isAlias(char *s, LinkedList *theList);

void executeAlias(char *s, LinkedList *theList);

int isUnAlias(char *s);

void unAliasCommand(char *s, LinkedList *theList);
#endif 
