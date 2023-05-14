#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 // number of philosophers
#define LEFT (i + N - 1) % N // index of left neighbor
#define RIGHT (i + 1) % N // index of right neighbor
#define THINKING 0 // philosopher is thinking
#define HUNGRY 1 // philosopher is hungry
#define EATING 2 // philosopher is eating

int state[N]; // current state of each philosopher
int phil[N] = {0, 1, 2, 3, 4}; // indices of philosophers
sem_t mutex; // mutual exclusion semaphore
sem_t phil_sem[N]; // one semaphore per philosopher

void test(int i) {
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        printf("Philosopher %d is eating\n", i);
        sem_post(&phil_sem[i]);
    }
}

void grab_forks(int i) {
    sem_wait(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is hungry\n", i);
    test(i);
    sem_post(&mutex);
    sem_wait(&phil_sem[i]);
    usleep(1000);
}

void put_forks(int i) {
    sem_wait(&mutex);
    state[i] = THINKING;
    printf("Philosopher %d is thinking\n", i);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void *philosopher(void *arg) {
    int *i = (int *) arg;
    while (1) {
        usleep(1000);
        grab_forks(*i);
        usleep(1000);
        put_forks(*i);
    }
}

int main() {
    pthread_t thread_id[N];
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < N; i++) {
        sem_init(&phil_sem[i], 0, 0);
    }
    for (int i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        printf("Philosopher %d is thinking\n", i);
    }
    for (int i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }
    return 0;
}
