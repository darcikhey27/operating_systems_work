/*
 * lab1.h
 *
 *  Created on: Apr 3, 2017
 *      Author: ssteiner
 */

#ifndef LAB1_H_
#define LAB1_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
/**
 * This is the address structure for Lab 1 <br>
 * The address structure contains a char * for street, city and state, and an int for zip
 */
struct address
{
	char *street;
	char *city;
	char *state;
	int zip;
};

/**
 * I prefer named structures over anonymous structures
 */
typedef struct address Address;

/**
 * the openFile method prompts the user for the name of an input file.  The function
 * ensures the file opened properly and the open file is returned.  The function will prompt
 * for a file name until the file is opened
 *
 * @return FILE * representing the open file
 */
FILE * openFile();


Address * fillArray(int * total, FILE * fin);


int menu();
void printArray(int total, Address * array);
void printStreetSortedArray(Address * array, int total);
void printCitySortedArray(Address * array, int total);
void printZipSortedArray(int total, Address * array);
void cleanUp(Address * array, int total);
void strip(char * array);

#endif /* LAB1_H_ */
