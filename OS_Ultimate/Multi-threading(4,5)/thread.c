// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>

// void *thread_function(void *arg)
// {
//     printf("Hello from the new thread!\n");
//     pthread_exit(NULL);
// }

// int main()
// {
//     pthread_t my_thread;
//     int ret = pthread_create(&my_thread, NULL, thread_function, NULL);
//     if (ret != 0) {
//         printf("Error: pthread_create() failed\n");
//         exit(-1);
//     }
//     printf("Created new thread with ID %ld\n", my_thread);
//     pthread_exit(NULL);
// }


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function to be executed by the thread
void *thread_function(void *arg)
{
    int thread_number = (int) arg;
    printf("Hello from thread %d!\n", *thread_number);
    pthread_exit(NULL);
}

int main()
{
    int num_threads = 3;
    pthread_t threads[num_threads];
    int thread_args[num_threads];

    // Create threads
    for (int i = 0; i < num_threads; i++) {
        thread_args[i] = i + 1;
        int ret = pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
        if (ret) {
            printf("Error: pthread_create failed!\n");
            exit(-1);
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < num_threads; i++) {
        int ret = pthread_join(threads[i], NULL);
        if (ret) {
            printf("Error: pthread_join failed!\n");
            exit(-1);
        }
    }

    printf("All threads have completed.\n");
    pthread_exit(NULL);
}