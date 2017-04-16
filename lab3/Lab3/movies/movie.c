#include <stdlib.h>
#include <stdio.h>

#include "movie.h"
#include "actor.h"

void cleanTypeMovie(void * ptr) {
    if(ptr == NULL) {
        puts("ptr is null");
        exit(-99);
    }
    int i;
    Movie *movie = (Movie*) ptr;
    for(i = 0; i < movie->totalActors; i++) {
        free(movie->actors[i].first);
        free(movie->actors[i].last);
        movie->actors[i].first = NULL;
        movie->actors[i].last = NULL;
    }
    free(movie->actors);
    movie->actors = NULL;
    free(movie->title);
    movie->title = NULL;
    free(movie);
    movie = NULL;
}

void* buildTypeMovie(FILE *fin) {
    if(fin == NULL) {
        puts("fin is null");
        exit(-99);
    }
    int numOfMovies = 0;
    char title[MAX];
    int totalActors = 0;

    char temp[MAX];
    char tempLine[5];

    // The movie contains an array of actors with first and last emembers

    fscanf(fin, "%d", &numOfMovies);
   // printf("noOfmovies %d\n", numOfMovies);

    // title
    fgets(title, MAX, fin);
    strip(title);
    //printf("title: %s\n", title);

    // total actors
    fscanf(fin, "%d" , &totalActors);
    //printf("total actors %d\n", totalActors);

    Actor *actors = (Actor*) malloc(sizeof(Actor) * totalActors);
    int i; 
    for(i = 0; i < totalActors; i++) {
        char first[MAX];
        char last[MAX];
        fscanf(fin, "%s %s", first, last);
        strip(first);
        strip(last);

        actors[i].first = (char*) malloc(strlen(first)+1);
        strcpy(actors[i].first, first);
        actors[i].last = (char*) malloc(strlen(last)+1);
        strcpy(actors[i].last, last);
    }
    Movie *movie = (Movie*) malloc(sizeof(Movie));
    movie->actors = actors;
    movie->totalActors = totalActors;
    movie->title = (char*) malloc(strlen(title)+ 1);
    strcpy(movie->title, title);

    return movie;
}

void printTypeMovie(void* passedIn) {
    Movie movie = *((Movie*) passedIn);
    printf("Movie title: %s\n", movie.title);

    int actors = movie.totalActors;
    for(int i = 0; i < actors; i++) {
        printf("%s %s\n", movie.actors[i].first, movie.actors[i].last);
    }
}

void * buildTypeMovie_Prompt(FILE * fin) {
    char title[MAX];
    int totalActors;
    Actor *actors;
    char first[MAX];
    char last[MAX];
    int i;

    printf("Enter the title for the movie: ");
    fgets(title, MAX, fin);
    strip(title);
    
    printf("Enter total actors: ");
    fscanf(fin, "%d", &totalActors);

    actors = (Actor*) malloc(sizeof(Actor) * totalActors);

    for(i = 0; i < totalActors; i++) {
        printf("Enter name <space> lastname for actor %d: ", i+1);
        fscanf(fin, "%s %s", first, last);
        strip(first);
        strip(last);

        actors[i].first = (char*) malloc(strlen(first)+ 1);
        strcpy(actors[i].first, first);

        actors[i].last = (char*) malloc(strlen(last)+1);
        strcpy(actors[i].last, last);
    }

    Movie *movie  = (Movie*) malloc(sizeof(Movie));
    movie->actors = actors;
    movie->totalActors = totalActors;
    movie->title = (char*) malloc(strlen(title)+ 1);
    strcpy(movie->title, title);

    return movie;
}

int compareMovie(const void * p1, const void * p2) {
    
    if(p1 == NULL || p2 == NULL) {
        puts("p1 or p2 is NULL");
        exit(-99);
    }
    Movie left = *((Movie*) p1);
    Movie right = *((Movie*) p2);
    
    if(strcmp(left.title, right.title) > 0) {
        return 1;
    }
    else if(strcmp(left.title, right.title) < 0) {
        return -1;
    }
    else {
        return left.totalActors - right.totalActors;
    }

}

