#ifndef HISTORYUTIL_H
#define HISTORYUTIL_H
#include <stdlib.h>
#include "../linkedlist/linkedList.h"


void writeHistoryFile(FILE *fin, LinkedList *theList);

int isHistoryCommand(char *);

 
void displayTheHistory(int count, LinkedList *theList);
#endif 

