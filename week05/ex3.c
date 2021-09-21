#include "pthread.h"
#include "stdlib.h"
#include "stdio.h"
#include <unistd.h>

typedef struct buffer {
    pthread_cond_t consumer_cond;
    pthread_mutex_t consumer_mutex;
    pthread_cond_t producer_cond;
    pthread_mutex_t producer_mutex;
    int *values;
    int capacity;
    int length;
} buffer_t;

void consumer(buffer_t *buf) {
    while (1) {
        if (buf->length == 0) pthread_cond_wait(&buf->consumer_cond, &buf->consumer_mutex);
        printf("Consumed data with length: %d\n", buf->length);
        for (int i = 0; i < buf->length; i++) {
            printf("Data #%d: %d\n", i + 1, buf->values[i]);
            buf->values[i] = 0;
        }
        buf->length = 0;
        pthread_cond_signal(&buf->producer_cond);
        int time = rand() % 3;
        sleep(time);
    }
}

void producer(buffer_t *buf) {
    while (1) {
        int length = (rand() % (5 - 1)) + 1;
        int *values = malloc(length * sizeof(int));
        for (int i = 0; i < length; i++) {
            values[i] = rand() % 200;
        }
    	if (buf->length != 0) pthread_cond_wait(&buf->producer_cond, &buf->producer_mutex);
  	printf("Producing data with length: %d\n", length);
  	for (int i = 0; i < length; i++) {
            buf->values[i] = values[i];
       	    printf("Produced: %d\n", buf->values[i]);
 	}
  	buf->length = length;
 	pthread_cond_signal(&buf->consumer_cond);
        free(values);
        sleep(3);
    }
}

int main() {
    buffer_t *buf = malloc(sizeof(buffer_t));
    buf->capacity = 5;
    buf->length = 0;
    buf->values = malloc(5 * sizeof(int));

    pthread_cond_init(&buf->consumer_cond, NULL);
    pthread_mutex_init(&buf->consumer_mutex, NULL);
    pthread_cond_init(&buf->producer_cond, NULL);
    pthread_mutex_init(&buf->producer_mutex, NULL);
    
    pthread_t producer_thread;
    pthread_create(&producer_thread, NULL, producer, buf);
    pthread_t consumer_thread;
    pthread_create(&consumer_thread, NULL, consumer, buf);
    pthread_join(producer, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_cond_destroy(&buf->consumer_cond);
    pthread_mutex_destroy(&buf->consumer_mutex);
    pthread_cond_destroy(&buf->producer_cond);
    pthread_mutex_destroy(&buf->producer_mutex);
    free(buf->values);
    free(buf);
}

