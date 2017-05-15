#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "cscd340Lab9.h"
#include "utils/myUtils.h"


int curr;
int32_t PAGES;
int32_t PAGE_FRAMES;


int main() {
    FILE *fin = NULL;

    uint32_t my_32bit_int;
    uint32_t VAS_size = 0;
    uint32_t PAS_size = 0;
    uint32_t sizeOfPage = 0;
    curr = 0;

    setup(&VAS_size, &PAS_size, &sizeOfPage);

    uint32_t offset = getOffset(sizeOfPage);
    //printf("offset is %d\n", offset);
    uint32_t pages = computePages(VAS_size, sizeOfPage);
    uint32_t pageFrames = computePages(PAS_size, sizeOfPage);
    PAGES = pages;
    PAGE_FRAMES = pageFrames;

    PTE pagesArray[pages];

    initPages(pagesArray, pages);

    PF pagesFrameArray[pageFrames];
    initFrames(pagesFrameArray, pageFrames);


    // ask for the file two here
    fin = readMemoryFile();
    uint32_t memCount = countMemoryFile(fin);

    processMemory(memCount, fin, offset, pagesArray, pagesFrameArray);

    //printf("end\n");


    fclose(fin);
    return 0;
}
void initFrames(PF *pagesFrameArray, int size) {

    for(int i = 0; i < size; i++) {
        pagesFrameArray[i].pageMappedTo = 0;
    }
}

void initPages(PTE *pages, int size) {
    for(int i = 0; i < size; i++) {
        pages[i].page = 0;
        pages[i].presentBit = 0;
    }
}

void processMemory(int memCount, FILE* fin, int offset, PTE *pageArray, PF *frameArray) {
    // read an address and determine the page for that address
    //printf("mem count %d\n", memCount);

    int address = 0;
    for(int i = 0; i <= memCount; i++) {
        fscanf(fin, "%d", &address);
        //determine page for this address
        //printf("adress: %d, hex: %x\n", address, address);
        uint32_t pageNum = getPageNumber(address, offset);
        //printf("pagenum: %d\n", pageNum);
        uint32_t location;
        uint32_t page;
        location = isAvailablePageFrame(frameArray);
        if(pageArray[pageNum].presentBit != 1) { // if page is not mapped
            if(location == -1) {
                // evict(frameArray, curr)
                // map(frame, curr);
                perror("about to evict some stuff");
                //exit(-1);
            }
            else {// map it
                pageArray[pageNum].presentBit = 1;
                pageArray[pageNum].page = location;
                frameArray[location].pageMappedTo = pageNum; 
            }
        } 
        else {
            // get the page frame, then concatenate to address off by offset
            location = pageArray[pageNum].page;
        }
        //  printf("i = %d\n", i);
        printf("virtual address: %d\nPage Number: %d\nPage frame number: %d\nPysical Adress% d\n\n", 
                address, pageNum, location, displayPage(location, address, offset));
    }//end for
    rewind(fin);
}

int displayPage(int page, int address, int offset) {

    //printf("page: %d\n", page);
    address = address << 24;

    uint32_t left = page;
    uint32_t right = (address >> 24);
    //puts("----------------------------------");
    //printf("left: %d right: %d\n", left, right);
    //puts("----------------------------------");

    printf("===================================\n"); 
    return (left << 8)|right;
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
    int32_t retNum = num;
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
