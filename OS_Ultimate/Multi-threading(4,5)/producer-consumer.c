#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10 // size of buffer
#define MAX_ITEMS 100 // maximum number of items to produce

int buffer[BUFFER_SIZE]; // buffer for items
int in = 0; // index for inserting into buffer
int out = 0; // index for removing from buffer
int count = 0; // number of items in buffer

sem_t empty; // semaphore for empty slots in buffer
sem_t full; // semaphore for full slots in buffer
pthread_mutex_t mutex; // mutex for buffer access

void *producer(void *arg) {
    int item = 1;
    while (item <= MAX_ITEMS) {
        sem_wait(&empty); // wait for an empty slot in buffer
        pthread_mutex_lock(&mutex); // lock buffer access
        buffer[in] = item; // insert item into buffer
        printf("Producer produced item %d\n", item);
        in = (in + 1) % BUFFER_SIZE; // update index for inserting into buffer
        count++;
        pthread_mutex_unlock(&mutex); // unlock buffer access
        sem_post(&full); // signal that a slot in buffer is full
        item++;
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&full); // wait for a full slot in buffer
        pthread_mutex_lock(&mutex); // lock buffer access
        item = buffer[out]; // remove item from buffer
        printf("Consumer consumed item %d\n", item);
        out = (out + 1) % BUFFER_SIZE; // update index for removing from buffer
        count--;
        pthread_mutex_unlock(&mutex); // unlock buffer access
        sem_post(&empty); // signal that a slot in buffer is empty
        if (item == MAX_ITEMS) break;
    }
    pthread_exit(NULL);
}

int main() {
    sem_init(&empty, 0, BUFFER_SIZE); // initialize empty semaphore
    sem_init(&full, 0, 0); // initialize full semaphore
    pthread_mutex_init(&mutex, NULL); // initialize mutex

    pthread_t prod, cons;

    pthread_create(&prod, NULL, producer, NULL); // create producer thread
    pthread_create(&cons, NULL, consumer, NULL); // create consumer thread

    pthread_join(prod, NULL); // wait for producer thread to finish
    pthread_join(cons, NULL); // wait for consumer thread to finish

    sem_destroy(&empty); // destroy empty semaphore
    sem_destroy(&full); // destroy full semaphore
    pthread_mutex_destroy(&mutex); // destroy mutex

    return 0;
}
