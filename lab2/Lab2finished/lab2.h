#ifndef LAB2_H_
#define LAB2_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

struct Stock
{
   char *symbol;
   char *name;
   double price;

};

typedef struct Stock stock;

int fillArray(struct Stock array[], FILE * fin);
int menu();
void printArray(struct Stock array[], int total);

int compareSymbols(const void * one, const void * two);
int compareNames(const void * one, const void * two);
int comparePrices(const void * one, const void * two);

void cleanUp(stock * array, int total);
void strip(char *s);



#endif

