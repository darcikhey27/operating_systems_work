#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "listUtils.h"
//#include "../words/word.h"

Node * buildNode(FILE * fin, void *(*buildData)(FILE * in) ) {

    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->data = buildData(fin);
    // added this
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

Node * buildNode_Type(void * passedIn) {
    // added this line today
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = passedIn;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

void sort(LinkedList * theList, int (*compare)(const void *, const void *)) {

    if(theList == NULL) {
        puts("theList is null");
        exit(-99);
    }
    if(theList->size == 0 || theList->size == 1) {
        return;
    }

    Node *pos, *min, *searcher;
    void* temp;

    for(pos = theList->head->next; pos != NULL; pos = pos->next) {
        min = pos;

        for(searcher = pos->next; searcher != NULL; searcher = searcher->next) {
            if(compare(min->data, searcher->data) > 0) {
                min = searcher;
            }
        }
        temp = pos->data;
        pos->data = min->data;
        min->data = temp;
    }
}

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

        //Node *newNode = (Node*) malloc(sizeof(Node)); 
        Node *newNode = buildNode_Type(buildData(fin));

        //newNode->data = buildData(fin);

        addFirst(myList, newNode);
    }
}
