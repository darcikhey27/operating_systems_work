#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cscd340Lab9.h"

int main() {
    FILE *fin = NULL;
    int VAS_size = 0;
    int PAS_size = 0;
    int sizeOfPage = 0;

    setup(&VAS_size, &PAS_size, &sizeOfPage);
    
    int pages = computePages(VAS_size, sizeOfPage);
    int pageFrames = computePages(PAS_size, sizeOfPage);
    
    PTE pagesArray[pages];
    PF pagesFrameArray[pageFrames];

    printf("end\n");

    return 0;
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
    fscanf(fin, "%d", &sizeofPAS);
    fscanf(fin, "%d", &pageSize);
    
    *VAS_size = sizeofVAS;
    *PAS_size = sizeofPAS;
    *sizeOfPage = pageSize;

    //printf("%d %d %d\n", a, b, c);
    rewind(fin);
    fclose(fin);
}
