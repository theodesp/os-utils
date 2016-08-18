#include <stdio.h>
#include <pthread.h>
// remember to set compilation option -pthread

// Create a mutex this ready to be locked!
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int sum = 0; //shared toxic variable
int sum2 = 0; //shared toxic variable
int sum3 = 0; //shared toxic variable

void *counter(void *param) {
    int i; //local to each thread
    for (i = 0; i < 10000000; i++) {
        // The code does not stop two threads from reading-writing sum at the same time
        // Both threads copy the current value of sum into CPU that runs 
        // each thread (for example 123). 
        // Both threads increment one to their own copy.
        sum += 1;
    }
    return NULL;
}

void *safecounter(void *param) {
    int i; //local to each thread

    // Same thread that locks the mutex must unlock it
    // Critical section is just 'sum += 1'
    // However locking and unlocking a million times
    // has significant overhead

    pthread_mutex_lock(&m);

    // Other threads that call lock will have to wait until we call unlock

    for (i = 0; i < 10000000; i++) {
        sum2 += 1;
    }
    pthread_mutex_unlock(&m);
    return NULL;
}

void *bestcounter(void * param) { // A faster multi-thread example
    int i; //local to each thread
    int local = 0;
    for (i = 0; i < 10000000; i++) {
       local += 1;
    }

    pthread_mutex_lock(&m);
    sum3 += local;
    pthread_mutex_unlock(&m);

    return NULL;
}

int main() {
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, counter, NULL);
    pthread_create(&tid2, NULL, counter, NULL);

    //Wait for both threads to finish:
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Sum is %d\n", sum); // Will print different result every time
    
    pthread_t tid3, tid4;
    pthread_create(&tid3, NULL, safecounter, NULL);
    pthread_create(&tid4, NULL, safecounter, NULL);

    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);

    printf("Sum is %d\n", sum2); // Will print the currect same result every time
    
    pthread_t tid5, tid6;
    pthread_create(&tid5, NULL, bestcounter, NULL);
    pthread_create(&tid6, NULL, bestcounter, NULL);

    //Wait for both threads to finish:
    pthread_join(tid5, NULL);
    pthread_join(tid6, NULL);

    printf("Sum is %d\n", sum3); // Will print the currect same result every time
    
    return 0;
}
