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

    puts("-----------------------");

    int first = 0xA;  // 1010;
    int second = 0x3; // 0011;
    printf("first %x second %x\n", first, second);
    int result = (first << 4) | second;
    printf("%X\n", result);


    return 0;
}
