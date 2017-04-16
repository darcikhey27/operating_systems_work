#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "listUtils.h"
#include "../words/word.h"

void buildListTotal(LinkedList * myList, int total, FILE * fin, 
        void * (*buildData)(FILE * in)) {

    if(myList == NULL) {
        puts("myList is null");
        exit(-99);
    }
    if(total <= 0) {
        puts("total is < 0");
        exit(-99);
    }

    for(int i = 0; i < total; i++) {

        Node *newNode = (Node*) malloc(sizeof(Node)); 
        newNode->data = buildData(fin);

        addFirst(myList, newNode);
    }
}


Node * buildNode(FILE * fin, void *(*buildData)(FILE * in) ) {

    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->data = buildData(fin);
    return newNode;

}
