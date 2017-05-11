#ifndef CSCD340LAB9_H
#define CSCD340LAB9_H

struct pageTableEntry {
    int pageFrame;
    int presentBit;
};
typedef struct pageTableEntry PTE;

struct pageFrame {
    int page;
};
typedef struct pageFrame PF;


void setup(int *a, int *b, int *c);

int computePages(int vas, int sizeOfPage);




#endif
