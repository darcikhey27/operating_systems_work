#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#include "linkedList.h"
#include "../history/history.h"

int HISTCOUNTER = 0;


LinkedList* linkedList() {
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = (Node*) malloc(sizeof(Node));
    list->head->data = NULL;
    list->head->next = list->head;
    list->head->prev = list->head;
    list->size = 0;

    return list;
}

void addLast(LinkedList* theList, Node *nn) {
    if(theList == NULL) {
        puts("the list is null");
        exit(-99);
    }
    if(nn == NULL) {
        // I dont want to exit here because if nn is not an alias object I can't exit
        puts("the nn is null");
        exit(-99);
    }
    HISTCOUNTER++;
    //History item = *((History*)nn->data);
   // item.bangNumber = HISTCOUNTER;
    //item.bangNumber++;

    if(theList->head->next == theList->head) {
        addFirst(theList, nn);
        return;
    }
    Node *curr = theList->head->next;
    while(curr->next != theList->head) {
        curr = curr->next;
    }
    curr->next = nn;
    nn->prev = curr;
    //nn->next = NULL;
    nn->next = theList->head;
    theList->head->prev = nn;

    theList->size++;

}

void addFirst(LinkedList *theList, Node *nn) {

    if(theList == NULL) {
        puts("theList is null");
        exit(-99);
    }
    if(nn == NULL) {
        puts("the nn is null");
        exit(-99);
    }
    // added
    if(theList->head->next == theList->head) {
        //nn->next = NULL;
        nn->prev = theList->head;
        theList->head->next = nn;

        nn->next = theList->head;
        theList->head->prev = nn;
        theList->size++;
        return;
    }
    nn->prev = theList->head;
    nn->next = theList->head->next;
    theList->head->next = nn;
    nn->next->prev = nn;

    theList->size++;
}

void removeFirst(LinkedList * theList, void (*removeData)(void *)) {

    if(theList == NULL) {
        puts("theList is null");
        exit(-99);
    }
    Node *curr = theList->head->next;
    theList->head->next = curr->next;
    removeData(curr->data);
    free(curr);
    curr = NULL;

    theList->size--;
}

void removeLast(LinkedList * theList, void (*removeData)(void *)) {
    if(theList == NULL) {
        puts("theList is null");
        exit(-99);
    }
    Node *temp = theList->head->next;
    Node *t;
    while(temp->next != NULL) {
        t = temp;
        temp = temp->next;
    }
    removeData(t->next->data);
    free(t->next);
    t->next  = NULL;
    theList->size--;
}

void removeItem(LinkedList * theList, Node * nn, void (*removeData)(void *), 
        int (*compare)(const void *, const void *) ) {

    if(theList == NULL) {
        puts("theList is null");
        exit(-99);
    }
    if(nn == NULL) {
        puts("nn is null");
        exit(-99);
    }

    Node *curr = theList->head->next;
    Node *prev = theList->head;
    while(curr != NULL) {
        if(compare(curr->data, nn->data) == 0) {
            prev->next = curr->next;

            removeData(curr->data);
            free(curr);
            curr = NULL;

            // i added this line 22:11
            removeData(nn->data);
            free(nn);
            nn = NULL;
            theList->size--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void clearList(LinkedList * theList, void (*removeData)(void *)) {
    Node *current = theList->head->next;
    Node *next;
    while(current != theList->head) {
        next = current->next;
        removeData(current->data);
        free(current);
        current = next;
    }
    free(theList->head);
    //puts("A list has been deleted");
}
void printList(const LinkedList * theList, void (*convertData)(void *)) {

    if(theList ==  NULL) {
        puts("Empty List");
        return;
    }
    Node *curr = theList->head->next;
    //puts("-----------------------------------------");
    while(curr != theList->head) {
        convertData(curr->data);
        curr = curr->next;
    }
    //puts("-----------------------------------------");
}
