#ifndef ALIASUTIL_H_
#define ALIASUTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../linkedlist/linkedList.h"
#include "../utils/myUtils.h"
#include "../tokenize/makeArgs.h"

/* will traverse the alias linkedlist, if it
 * finds a match of s it will execute the 
 * tokenized command with execvp(...)
 */
int isAlias(char *s, LinkedList *theList);

void executeAlias(char *s, LinkedList *theList);

#endif 
