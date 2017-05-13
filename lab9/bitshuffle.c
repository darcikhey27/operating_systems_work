#include <stdlib.h>
#include <stdio.h>

int main() {

    int num = 16916;

    printf("%d\n", num);
    printf("%x\n", num);

    num = num >> 8;
    
    printf("-----------------------------\n");
    printf("base10: %d\n", num);
    printf("hex: %x\n", num);
    
    return 0;
}
