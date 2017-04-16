/**
 * The file that contains main is meant to
 * test your generic linked class using a basic
 * set of functions.
 *
 * @note This file will never be changed
 */
#include "./utils/myUtils.h"
#include "./utils/fileUtil.h"
#include "./linkedlist/listUtils.h"
#include "./linkedlist/linkedList.h"
#include "./linkedlist/requiredIncludes.h"

int main()
{

    int total, choice;
    FILE * fin = NULL;

    LinkedList * wordList = linkedList();
    fin = openInputFileType_Prompt("words");
    total = countRecords(fin, 1);
    buildListTotal(wordList, total, fin, buildTypeWord);
    fclose(fin);
    
    /*
    printList(wordList, printTypeWord);

    addFirst(wordList, buildNode(stdin, buildTypeWord_Prompt));

    addLast(wordList, buildNode(stdin, buildTypeWord_Prompt));

    removeFirst(wordList, cleanTypeWord);
    printList(wordList, printTypeWord);


    puts("removeItem");

    removeItem(wordList, buildNode(stdin, buildTypeWord_Prompt), cleanTypeWord, compareWord);

    printList(wordList, printTypeWord);

*/

    // started working on the movie list 
    LinkedList * movieList = linkedList();
    fin = openInputFileType_Prompt("movies");
    total = readTotal(fin);
    buildListTotal(movieList, total, fin, buildTypeMovie);
    fclose(fin);

    puts("addFirst moive");
    addFirst(movieList, buildNode(stdin, buildTypeMovie_Prompt));
    printList(movieList, printTypeMovie);

    //puts("addlast movie");
    //addLast(movieList, buildNode(stdin, buildTypeMovie_Prompt));
    //printList(movieList, printTypeMovie);

    //puts("Removing last movie"); 
   // removeLast(movieList, cleanTypeMovie);
    //printList(movieList, printTypeMovie);



    /*
       do
       {
       choice = menu();

       switch(choice)
       {

    // Words
    case 1: printList(wordList, printTypeWord);
    break;

    case 2: addFirst(wordList, buildNode(stdin, buildTypeWord_Prompt));
    break;

    case 3: addLast(wordList, buildNode(stdin, buildTypeWord_Prompt));
    break;

    case 4: sort(wordList, compareWord);
    break;

    case 5: removeFirst(wordList, cleanTypeWord);
    break;

    case 6: removeItem(wordList, buildNode(stdin, buildTypeWord_Prompt), cleanTypeWord, compareWord);
    break;


    // Movies
    case 7: printList(movieList, printTypeMovie);
    break;

    case 8: addFirst(movieList, buildNode(stdin, buildTypeMovie_Prompt));
    break;

    case 9: addLast(movieList, buildNode(stdin, buildTypeMovie_Prompt));
    break;

    case 10: removeLast(movieList, cleanTypeMovie);
    break; 

    case 11: removeItem(movieList, buildNode(stdin, buildTypeMovie_Prompt), cleanTypeMovie, compareMovie);
    break;

    }// end switch  

    }while(choice != 12); */

    clearList(wordList, cleanTypeWord);
    free(wordList);
    wordList = NULL;

    clearList(movieList, cleanTypeMovie);
    free(movieList);
    movieList = NULL;

    printf("Program Ended\n");

    return 0;

}// end main
