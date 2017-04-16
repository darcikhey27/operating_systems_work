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
    //Actor *actors = (Actor*) movie->actors;
    int total = movie->totalActors;
    for(i = 0; i < total; i++) {
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

    fscanf(fin, "%d", &numOfMovies);

    fgets(title, MAX, fin);
    strip(title);

    fscanf(fin, "%d" , &totalActors);

    Actor *actors = (Actor*) malloc(sizeof(Actor) * totalActors);
    int i; 
    for(i = 0; i < totalActors; i++) {
        char first[MAX];
        char last[MAX];
        fscanf(fin, "%s %s", first, last);
        strip(first);
        strip(last);

        actors->first = (char*) malloc(strlen(first)+1);
        strcpy(actors->first, first);
        actors->last = (char*) malloc(strlen(last)+1);
        strcpy(actors->last, last);
    }
    Movie *movie = (Movie*) malloc(sizeof(Movie));
    movie->actors = actors;
    movie->totalActors = totalActors;
    movie->title = (char*) malloc(strlen(title)+ 1);
    strcpy(movie->title, title);
    return movie;
}

void printTypeMovie(void* passedIn) {
    /*
       Movie movie = *((Movie*) passedIn);
       printf("Movie title: %s\n", movie.title);

       int actors = movie.totalActors;
       for(int i = 0; i < actors; i++) {
       printf("%s %s\n", movie.actors[i].first, movie.actors[i].last);
       } */
}

