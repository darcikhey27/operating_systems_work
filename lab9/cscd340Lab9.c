#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "cscd340Lab9.h"
#include "utils/myUtils.h"
int curr;
int PAGES;
int PAGE_FRAMES;
int main() {
    FILE *fin = NULL;
    int VAS_size = 0;
    int PAS_size = 0;
    int sizeOfPage = 0;
    curr = 0;

    setup(&VAS_size, &PAS_size, &sizeOfPage);

    int offset = getOffset(sizeOfPage);
    //printf("offset is %d\n", offset);
    int pages = computePages(VAS_size, sizeOfPage);
    int pageFrames = computePages(PAS_size, sizeOfPage);
    PAGES = pages;
    PAGE_FRAMES = pageFrames;

    PTE pagesArray[pages];
    PF pagesFrameArray[pageFrames];

    // ask for the file two here
    fin = readMemoryFile();
    int memCount = countMemoryFile(fin);

    processMemory(memCount, fin, offset, pagesArray, pagesFrameArray);

    //printf("end\n");


    fclose(fin);
    return 0;
}
void processMemory(int memCount, FILE* fin, int offset, PTE *pageArray, PF *frameArray) {
    // read an address and determine the page for that address
    int address = 0;
    for(int i = 0; i <= memCount; i++) {
        fscanf(fin, "%d", &address);
        //determine page for this address
        //printf("adress: %d, hex: %x\n", address, address);

        int pageNum = getPageNumber(address, offset);
        //printf("pagenum: %d\n", pageNum);

        if(pageArray[pageNum].presentBit != 1) {
            //page is not mapped
            int location = isAvailablePageFrame(frameArray);
            
            if(location -1) {
                // evict(frameArray, curr)
                // map(frame, curr);
                perror("about to evict some stuff");
                exit(-1);
            }
            else {
                //update(frameArray, pageNum);
            }
        } 
        else {
            pageArray[pageNum].presentBit = 1;
            
        } 
        printf("virtual address: %d\nPage Number: %d\nPage frame number: %d\nPysical Adress% d\n", 
                address, pageNum, curr, 0);
    }
    rewind(fin);
}
int isAvailablePageFrame(PF *frameArray) {
    int i;
    for(i = 0; i < PAGE_FRAMES; i++) {
        //printf("pageFrame[%d] is %d\n", i, frameArray[i].pageMappedTo);
        if(frameArray[i].pageMappedTo == 0) {
            return i;
        }
        if(i == PAGE_FRAMES-1) {
            return -1;
        }
    }
}
int getPageNumber(int num, int offset) {
    int retNum = num;
    retNum = retNum >> offset;
    return retNum;
}
int countMemoryFile(FILE *fin) {
    int memoryCount = 0;
    char line[BUFSIZ];

    fgets(line, MAX, fin);
    while(!feof(fin)) {
        memoryCount++;
        fgets(line, MAX, fin);
    }
    rewind(fin);
    //printf("there are %d lines in file\n", memoryCount);
    return memoryCount;
}
FILE* readMemoryFile() {
    char filename[BUFSIZ];
    FILE *fin = NULL;

    printf("Enter filename: ");
    fgets(filename, BUFSIZ, stdin);
    strip(filename); 
    fin = fopen(filename, "r");
    if(fin != NULL) {
        return fin;
    }
    perror("fin is null");
    exit(-1);
}

int getOffset(int sizeofPage) {
    int bits;
    bits = log(sizeofPage) / log(2);

    return bits;
}
int computePages(int type_size, int sizeOfPage) {
    return type_size / sizeOfPage;
}

void setup(int *VAS_size, int *PAS_size, int *sizeOfPage) {
    FILE *fin = fopen("setup.txt", "r");
    int sizeofVAS = 0;
    int sizeofPAS  = 0;
    int pageSize = 0;
    fscanf(fin, "%d", &sizeofVAS);
    fscanf(fin, "%d", &pageSize);
    fscanf(fin, "%d", &sizeofPAS);

    //printf("sizeOfVAS %d, sizeofPAS %d pageSize %d\n", sizeofVAS, sizeofPAS, pageSize);
    *VAS_size = sizeofVAS;
    *PAS_size = sizeofPAS;
    *sizeOfPage = pageSize;

    rewind(fin);
    fclose(fin);
}
