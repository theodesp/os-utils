#include <stdio.h>
#include <semaphore.h>
// remember to set compilation option -pthread

// A counting semaphore contains a value and supports two operations "wait" and "post". 
// Post increments the semaphore and immediately returns. "wait" will wait 
// if the count is zero. If the count is non-zero the semaphore decrements 
// the count and immediately returns.

sem_t s;
int main() {
    // int sem_init(sem_t *sem, int pshared, unsigned int value);
    // The pshared argument indicates whether this semaphore is to be shared
    // between the threads of a process, or between processes.
    sem_init(&s, 0, 10);
    
    // int sem_wait(sem_t *sem);
    sem_wait(&s); // Could do this 10 times without blocking. Decrement count
    
    // int sem_post(sem_t *sem);
    sem_post(&s); // Announce that we've finished (and one more resource item is available; increment count)
    sem_destroy(&s); // release resources of the semaphore
}