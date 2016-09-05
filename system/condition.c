#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// About condition variables

// Condition variables allow a set of threads to sleep until tickled!
// You can tickle one thread or all threads that are sleeping.
// If you only wake one thread then the operating system will decide
// which thread to wake up. You don't wake threads directly instead you 'signal'
// the condition variable, which then will wake up one (or all) threads
// that are sleeping inside the condition variable.

// Condition variables are used with a mutex and with a loop (to check a condition).

// Threads sleeping inside a condition variable are woken up by calling pthread_cond_broadcast
// (wake up all) or pthread_cond_signal (wake up one).

// The call pthread_cond_wait performs three actions:
//
// * Unlock the mutex and atomically...
// * Waits (sleeps until pthread_cond_signal is called on the same condition variable)
// * Before returning, locks the mutex

// Condition variables are always used with a mutex lock.

// Before calling wait, the mutex lock must be locked and wait must be wrapped with a loop.

pthread_cond_t cv;
pthread_mutex_t m;
int count;

// Initialize
pthread_cond_init(&cv, NULL);
pthread_mutex_init(&m, NULL);
count = 0;

pthread_mutex_lock(&m);
while (count < 10) {
   pthread_cond_wait(&cv, &m);
/* Remember that cond_wait unlocks the mutex before blocking (waiting)! */
/* After unlocking, other threads can claim the mutex. */
/* When this thread is later woken it will */
/* re-lock the mutex before returning */
}
pthread_mutex_unlock(&m);

//later clean up with pthread_cond_destroy(&cv); and mutex_destroy


// In another thread increment count:
while (1) {
  pthread_mutex_lock(&m);
  count++;
  pthread_cond_signal(&cv);
  /* Even though the other thread is woken up it cannot not return */
  /* from pthread_cond_wait until we have unlocked the mutex. This is */
  /* a good thing! In fact, it is usually the best practice to call */
  /* cond_signal or cond_broadcast before unlocking the mutex */
  pthread_mutex_unlock(&m);
}
