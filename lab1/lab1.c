/* Darci K Saucedo 
 * Lab 1
 * Operating Systems
 * 4/5/17
 */
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

#include "lab1.h"

FILE * openFile() {
    char fileName[MAX];
    char temp[MAX];
    int counter = 0;
    FILE *fin = NULL; 
    while(1) {

        printf("Ente the name of the file: ");
        scanf("%s", fileName);

        fin = fopen(fileName, "r");

        if(fin == NULL) {
            puts("fin is null");
            continue;
        }
        fgets(temp, MAX, fin);
        while(!feof(fin)) {
            counter++;
            fgets(temp, MAX, fin);
        }
        // make usre it is a good file
        if(counter %4 != 0 || counter == 0) {
            puts("incomplete or bad file");
            continue;
        }
        break;

    }
    rewind(fin);

    return fin;
}

Address * fillArray(int * total, FILE * fin){

    // read the file count the records
    char temp[MAX];
    int lines = 0;
    int records = 0;

    fgets(temp, MAX, fin);
    while(!feof(fin)) {
        lines++;
        fgets(temp, MAX, fin);
    }
    rewind(fin);

    records = lines / 4;
    *total= records;

    // dynamically create an array of address of the exact size
    Address *addresses = (Address*)malloc(sizeof(Address) * records);

    int index = 0;

    // fill that array using dynamic memory for each address return the filled array
    while(index != records) {

        char street[MAX];
        char city[MAX];
        char state[MAX];
        int zip;

        fgets(street, MAX, fin);
        strip(street);

        fgets(city, MAX, fin);
        strip(city);

        fgets(state, MAX, fin);
        strip(state);

        fscanf(fin, "%d", &zip);
        // printf("%d\n", zip);

        // eat the '\r' '\n' that was killing me for hours
        fgets(temp, MAX, fin);

        addresses[index].street = (char*) malloc(strlen(street)+1);
        strcpy(addresses[index].street, street);

        addresses[index].city = (char*) malloc(strlen(city)+1);
        strcpy(addresses[index].city, city);

        addresses[index].state = (char*) malloc(strlen(state)+1);
        strcpy(addresses[index].state, state);

        addresses[index].zip = zip;
        index++; 
    }

    return addresses;
}

int menu() {
    int choice = 0;
    do {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if(choice >= 1 && choice <= 4) {
            return choice;
        }
        puts("bad choice");

    }while(choice < 1 || choice > 4);

    return choice;
}

void printArray(int total, Address * array){
    int index = 0;

    char street[MAX];
    char city[MAX];
    char state[MAX];
    int zip;

    while(total != index) {
        strcpy(street, array[index].street);
        strcpy(city, array[index].city);
        strcpy(state, array[index].state);
        zip   = array[index].zip;

        puts(street);
        printf("%s %s %d\n", city, state, zip);
        puts("");
        index++;
    } 
}

void printStreetSortedArray(Address * array, int total) {
    puts("menu choice 1"); 
    int pos, min, searcher;

    Address temp;

    for(pos = 0; pos < total; pos++) {
        min = pos;
        for(searcher = pos + 1; searcher < total; searcher++) {

            if( strcmp(array[min].street, array[searcher].street ) > 0 ) {
                //
                min = searcher;
            } 
        }
        temp = array[pos];
        array[pos] = array[min];
        array[min] = temp;
    }
    printArray(total, array);

}

void printCitySortedArray(Address * array, int total) {
    puts("menu choice 2");
    int pos, min, searcher;
    Address temp;

    for(pos = 0; pos < total; pos++) {
        min = pos;
        for(searcher = pos + 1; searcher < total; searcher++) {

            if( strcmp(array[min].city, array[searcher].city) > 0 ) {
                //
                min = searcher;
            } 
        }
        temp = array[pos];
        array[pos] = array[min];
        array[min] = temp;

    }
    printArray(total, array);

}

void printZipSortedArray(int total, Address * array) {
    puts("menu choice 3");

    int pos, min, searcher;
    Address temp;

    for(pos = 0; pos < total; pos++) {
        min = pos;
        for(searcher = pos + 1; searcher < total; searcher++) {

            if(array[min].zip > array[searcher].zip) {
                min = searcher;
            } 
        }
        temp = array[pos];
        array[pos] = array[min];
        array[min] = temp;
    }
    printArray(total, array);

}
void cleanUp(Address * array, int total) {
    puts("in cleanup");
    int i, j;

    for(i = 0; i < total; i++) {
        free(array[i].street);
        array[i].street = NULL;
        free(array[i].city);
        array[i].city = NULL;
        free(array[i].state);
        array[i].state = NULL;
    }  
    free(array);
}

void strip(char *array) {
    int x = 0;
    while(array[x] != '\0') {
        if(array[x] == '\r') {
            array[x] = '\0';
        }
        else if(array[x] == '\n'){
            array[x] == '\0';
        }
        x++;
    }
}
