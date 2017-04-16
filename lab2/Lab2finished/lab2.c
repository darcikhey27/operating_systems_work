/* Darci K Saucedo
 * Lab2
 * OS
 * <mind wide open>
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lab2.h"



int fillArray2(struct Stock array[], FILE * fin) {
    // read fin,
    int index = 0;
    int counter = 0;
    int records = 0;
    char temp[MAX];

    fgets(temp, MAX, fin);
    while(!feof(fin)) {
        counter++;
        fgets(temp, MAX, fin);
    }
    rewind(fin);
    // count how many records
    records = counter / 3;

    // create the Stock array
    //stock  *stocks = (stock*)malloc(sizeof(stock) * records);
    // fill it
    while(index != records) {
        char symbol[MAX];
        char n[MAX];
        double price = 0.0;
        char temp[10]; 

        // get symbol
        fgets(symbol, MAX, fin);
        strip(symbol);
        // get name
        fgets(n, MAX, fin);
        strip(n);
        //get price
        fscanf(fin, "%lf", &price);

        // get rid of carriage line return
        fgets(temp, MAX, fin);

        // save data to array
        array[index].symbol = (char*) malloc(strlen(symbol)+1);
        strcpy(array[index].symbol, symbol);

        array[index].name = (char*)malloc(strlen(n) + 1);
        strcpy(array[index].name, n);
        array[index].price = price;

        index++; 
    }
    // return how many records
    return records;
}

void strip(char *array) {
    int x = 0;
    while(array[x] != '\0') {

        if(array[x] == '\r') {
            array[x] = '\0';
        }
        else if(array[x] == '\n'){
            array[x] = '\0';
        }
        x++;
    }
}

void printArray(struct Stock array[], int total) {
    int index = 0;
    while(total != index) {
        printf("%s - %s - %lf\n", array[index].symbol, 
                array[index].name, array[index].price);
        index++;
    } 
    puts("\n");
}

int menu() {
    int choice = 0;
    do {
        printf("Choice --> ");
        scanf("%d", &choice);

        if(choice >= 1 && choice <= 4) {
            return choice;
        }
        puts("bad choice");

    }while(choice < 1 || choice > 4);

    return choice;
}
int compareSymbols(const void * one, const void * two) {

    stock left = *((stock*) one);
    stock right = *((stock*) two);

    return strcmp(left.symbol, right.symbol);
}

int compareNames(const void * one, const void * two) {

    stock left = *((stock*) one);
    stock right = *((stock*) two);

    return strcmp(left.name, right.name);
}

int comparePrices(const void * one, const void * two) {

    stock left = *((stock*) one);
    stock right = *((stock*) two);

    return (left.price * 100) - (right.price * 100);
}

void cleanUp(stock* array, int total) {
    puts("in cleanup");
    int i, j;

    for(i = 0; i < total; i++) {
        free(array[i].symbol);
        array[i].symbol = NULL;
        free(array[i].name);
        array[i].name = NULL;
    }  
    //free(array);
}
