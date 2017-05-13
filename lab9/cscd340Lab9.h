#ifndef CSCD340LAB9_H
#define CSCD340LAB9_H


struct pageFrame {
    int curr;
    int pageMappedTo;
};
typedef struct pageFrame PF;


struct pageTableEntry {
    //struct pageFrame  *page;
    int page;
    int presentBit;
};
typedef struct pageTableEntry PTE;




void setup(int *a, int *b, int *c);

int computePages(int vas, int sizeOfPage);

int getOffset(int num);

FILE* readMemoryFile();

int countMemoryFile(FILE *fin);

void processMemory(int memCount, FILE *fin, int offset, PTE *pageArray, PF *frameArray);

int isAvailablePageFrame(PF *frames);

int getPageNumber(int n, int offset);

#endif
