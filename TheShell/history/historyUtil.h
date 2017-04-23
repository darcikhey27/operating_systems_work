#ifndef HISTORYUTIL_H
#define HISTORYUTIL_H
#include <stdlib.h>
#include "../linkedlist/linkedList.h"


void writeHistoryFile(FILE *fin, LinkedList *theList);

int isHistoryCommand(char *);

 
void displayTheHistory(LinkedList *theList);

int isExecuteHistory(char *s);

void executeHistNumber(char *s, LinkedList *theList);

int isBangBang(char *s);

void executeBangBang(LinkedList *theList);

#endif 

