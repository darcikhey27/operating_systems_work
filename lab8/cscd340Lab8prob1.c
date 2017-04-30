#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 10

pthread_mutex_t the_mutex; // binary semaphore
pthread_cond_t condc, condp; // counting metaphor producer and consumer
int buffer = 0;

void * consumer(void * ptr);
void * producer(void * ptr);

int main(int argc, char ** argv) {
    pthread_t pro, con; // producer, consurmer
    pthread_mutex_init(&the_mutex, 0); // zero is NULL 
    pthread_cond_init(&condc, 0);
    pthread_cond_init(&condp, 0);

    pthread_create(&pro, 0, producer,0);
    pthread_create(&con, 0, consumer,0);

    pthread_join(pro, 0);
    pthread_join(con, 0);

    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);
    pthread_mutex_destroy(&the_mutex);


}// end main

void * producer(void * ptr) {
    int x;
    for(x = 1; x <= MAX; x++) {
        pthread_mutex_lock(&the_mutex); // lock the mutex
        while(buffer != 0) {
            // passing the producer
            //printf("Producer with thread_id %ld is waiting\n",
            //                            pthread_self());
            pthread_cond_wait(&condp, &the_mutex); // sending a wait
        }// end while
        printf("Producer with thread_id %ld produced widget %d\n",
                pthread_self(), x);
        buffer++;
        // send the wake up signal
        pthread_cond_signal(&condc);
        pthread_mutex_unlock(&the_mutex);
    } // end for
    pthread_exit(0);
}// end producer

void * consumer(void * ptr) {
    int x;
    for(x = 1; x <= MAX; x++) {
        pthread_mutex_lock(&the_mutex); // lock the mutex
        while(buffer <= 0) {
            // passing the producer
            //printf("Consumer with thread_id %ld is waiting\n",
            //                           pthread_self());
            pthread_cond_wait(&condc, &the_mutex); // sending a wait
        }// end while
        printf("Consumer with thread_id %ld is consuming widget %d\n",
                pthread_self(), x);
        buffer--; 
        // send the wake up signal
        pthread_cond_signal(&condp);
        pthread_mutex_unlock(&the_mutex);
    } // end for
    pthread_exit(0);

}// end consumer
