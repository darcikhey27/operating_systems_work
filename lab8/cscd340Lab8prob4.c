#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 10
#define MAX_PRODUCER 2
#define MAX_CONSUMER 4

pthread_mutex_t the_mutex; // binary semaphore
pthread_cond_t condc, condp; // counting metaphor producer and consumer
int buffer[MAX];
int buffIndex = 0;
int num;

void * consumer(void * ptr);
void * producer(void * ptr);

int main(int argc, char ** argv) {

    num = 1;
    pthread_t pro[MAX_PRODUCER];
    pthread_t con[MAX_CONSUMER]; // producer, consurmer
    pthread_mutex_init(&the_mutex, 0); // zero is NULL 
    pthread_cond_init(&condc, 0);
    pthread_cond_init(&condp, 0);

    for(int i = 0; i < MAX_PRODUCER; i++) {
        pthread_create(&pro[i], 0, producer,0);
    }
    for(int i = 0; i < MAX_CONSUMER; i++) {
        pthread_create(&con[i], 0, consumer,0);
    }
    for(int i = 0; i < MAX_PRODUCER; i++) {
        pthread_join(pro[i], 0);
    }
    
    for(int i = 0; i < MAX_CONSUMER; i++) {
        pthread_join(con[i], 0);
    }

    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);
    pthread_mutex_destroy(&the_mutex);


}// end main

void * producer(void * ptr) {
    while(1) {
        pthread_mutex_lock(&the_mutex); // lock the mutex
        while(buffer[buffIndex] != 0) {
            printf("Producer with thread_id %ld is waiting\n",
                    pthread_self());
            pthread_cond_wait(&condp, &the_mutex); // sending a wait
            //sleep(1);
        }
        buffer[buffIndex] = num++;
        printf("Producer with thread_id %ld produced widget %d\n",
                pthread_self(), buffer[buffIndex]);

        // send the wake up signal
        pthread_cond_signal(&condc);
        pthread_mutex_unlock(&the_mutex);
    } // end for
    pthread_exit(0);

}// end producer

void * consumer(void * ptr) {
    while(1) {
        pthread_mutex_lock(&the_mutex); // lock the mutex
        while(buffer[buffIndex] <= 0) {
            // passing the producer
            printf("Consumer with thread_id %ld is waiting\n",
                    pthread_self());
            pthread_cond_wait(&condc, &the_mutex); // sending a wait
            //sleep(1);
        }// end while
        printf("Consumer with thread_id %ld is consuming widget %d\n",
                pthread_self(), buffer[buffIndex]);
        buffer[buffIndex] = 0; 
        // send the wake up signal
        pthread_cond_signal(&condp);
        pthread_mutex_unlock(&the_mutex);

    } // end for
    pthread_exit(0);
}// end consumer
