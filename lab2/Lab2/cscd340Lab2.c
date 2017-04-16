#include "fileUtil.h"
#include "lab2.h"

int main()
{
    FILE * fin = NULL;
    int total, choice;
    stock array[10]; // guaranteed 1 to 10 Stocks inclusive

    fin = openInputFile_Prompt();    
    puts("good fin");

    total = fillArray(array, fin);

    fclose(fin);

    do
    {
        choice = menu();
        switch(choice)
        {
            case 1:  qsort(array, total, sizeof(stock), compareSymbols);
                     printArray(array, total);
                     break;

            case 2:  qsort(array, total, sizeof(stock), compareNames);
                     printArray(array, total);
                     break;

            case 3:  qsort(array, total, sizeof(stock), comparePrices);
                     printArray(array, total);
                     break;

            case 4:	printf("all done\n");

        }// end switch

    }while(choice != 4);
    cleanUp(array, total);
    return 0;

}// end main
