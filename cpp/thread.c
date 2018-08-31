/*
https://www.tutorialspoint.com/cplusplus/cpp_multithreading.htm
Modified Andriy Zatserklyaniy <zatserkl@gmail.com> Aug 30, 2018

gcc thread.c -lpthread

or

clang thread.c -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

void *PrintHello(void *threadid) {
    long tid = (long)threadid;
    printf("Hello World! Thread ID, %ld\n", tid);
    pthread_exit(NULL);
}

int main () {
    pthread_t threads[NUM_THREADS];
    for (int i=0; i<NUM_THREADS; ++i) {
        printf("main() : creating thread, %d\n", i);
        // void *threadid = (void*)i; // warning: cast to pointer from integer of different size [-Wint-to-pointer-cast]
        void *threadid = (void*) (long)i;
        int rc = pthread_create(&threads[i], NULL, PrintHello, threadid);

        if (rc) {
            printf("Error:unable to create thread, %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
