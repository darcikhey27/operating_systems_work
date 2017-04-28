#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 100

pthread_mutex_t the_mutex;
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
	
		pthread_mutex_lock(&the_mutex);
		
		while(buffer != 0) {
			pthread_cond_wait(&condp, &the_mutex);
		}// end while
		buffer=x;
		pthread_cond_signal(&condc);
		pthread_mutex_unlock(&the_mutex);
	
	//	pthread_exit(?);
	} // end for

}// end producer


void * consumer(void * ptr) {


}// end consumer
