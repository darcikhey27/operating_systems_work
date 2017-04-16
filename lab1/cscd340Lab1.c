#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lab1.h"

int main()
{
	FILE * fin = NULL;
	int total, choice;
	Address * array = NULL;
	fin = openFile();

	array = fillArray(&total, fin);
	printArray(total, array);

	fclose(fin);
	fin = NULL;

	do
	{
		choice = menu();
		switch(choice)
		{
			case 1:	printStreetSortedArray(array, total);
				break;

			case 2: printCitySortedArray(array, total);
				break;

			case 3: printZipSortedArray(total, array);
				break;

			case 4:	printf("all done\n");
				break;

			default: perror("This is bad\n");
				 exit(-1);

		}// end switch

	}while(choice != 4);

	cleanUp(array, total);
	array = NULL;

	return 0;

}// end main
