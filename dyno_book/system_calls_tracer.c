#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {

    FILE *fin = NULL;
    char filename[20];

    printf("Enter filname: ");
    //fgets(filename, 20, stdin);
    scanf("%s", filename); 
    fin = fopen(filename, "r");
    if(fin == NULL) {
        puts("bad fin");
    }
    puts("end");

    


    return 0;
}
