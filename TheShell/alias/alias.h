#ifndef ALIAS_H_
#define ALIAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "actor.h"
#include "../utils/myUtils.h"
#include "../tokenize/makeArgs.h"

/**
 * @brief The alias data structure.
 *
 * A alias contains a title, an array of actors, and an int for the number
 *
 * @note I prefer named structures and then the typedef after the structure
 */
struct alias
{
   char *alias;
   char **tokenized_command;
};

typedef struct alias Alias;


/**
 * @brief Cleans up all dynamically allocated memory for the alias
 *
 * Cleans up and frees all the dynamically allocated memory 
 * In this case title, actors->first, actors->last and the actors array
 *
 * Each pointer in the specific data type is set to NULL after it has been freed.
 *
 * @param passedIn - The void * passed in representing the specific alias
 *
 * @warning - The passed in void * passedIn is checked - exit(-99) if NULL
 */
void cleanTypeAlias(void * ptr);


/**
 * @brief Builds and returns a single alias.
 *
 * Reads the initial data from the file and then builds
 * an object of type alias.
 *
 * @note The carriage return will be removed when reading from the file
 *
 * @param fin - The FILE * representing the open file
 * @return void * - Representing a alias object
 *
 * @warning - The passed in FILE * fin is checked - exit(-99) if NULL
 */
void * buildTypeAlias(FILE * fin);


/**
 * @brief Prints the specific alias.
 *
 * Format is title
 * Starting:
 * actor first actor last, actor first actor last
 *
 * @note: price is printed to two decimal places
 *
 * @param passedIn - The void * passed in representing a specific alias
 *
 * @warning - The passed in void * passedIn is checked - exit(-99) if NULL
 */
void printTypeAlias(void * passedIn);


/**
 * @brief Builds and returns a single alias.
 *
 * Reads the initial data from the keyboard by prompting the user.
 * A alias object is constructed.
 *
 * @note The carriage return will be removed when reading from the keyboard
 *
 * @param fin - The FILE * representing stdin
 * @return void * - Representing a alias object
 *
 * @warning - The passed in FILE * fin is checked - exit(-99) if NULL
 */
void * buildTypeAlias_Prompt(FILE * fin);


/**
 * @brief Compares two objects of type alias.
 *
 * aliass are compared based on title and if the title are the same then totalActors
 *
 * @note The passed in items will need to be cast to the appropriate alias type.
 *
 * @param p1 - The void * representing an object of type alias
 * @param p2 - The void * representing an object of type alias
 * @return int - Representing order < 0 indicates p1 is less than p2,
 * > 0 indicates p1 is greater than p2 and == 0 indicates p1 == p2 for contents
 *
 * @warning - The passed in void * p1 is checked - exit(-99) if NULL
 * @warning - The passed in void * p2 is checked - exit(-99) if NULL
 */
int compareAlias(const void * p1, const void * p2);


#endif /* MOVIE_H_ */
