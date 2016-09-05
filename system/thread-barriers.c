#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N (16)

//global variables
pthread_mutex_t m;
pthread_cond_t cv;
int remain = N;
double data[256][8192];

// When a thread reaches a barrier, it will wait at the barrier until all
// the threads reach the barrier, and then they'll all proceed together.

void *calc(void *ptr) {
// Thread 0 will work on rows 0..15, thread 1 on rows 16..31
	int x, y, start = N * (int) ptr; // Straight cast to int
	int end = start + N;
	for (x = start; x < end; x++)
		for (y = 0; y < 8192; y++) { /* do calc #1 */
		}

	pthread_mutex_lock(&m);
	remain--;
	if (remain == 0) {
		pthread_cond_broadcast(&cv);
	} else {
		while (remain != 0) { // wait in queue and unlock mutex
			pthread_cond_wait(&cv, &m);
		}
	}
	pthread_mutex_unlock(&m);
}

int main() {
	pthread_mutex_init(&m, NULL);
	pthread_cond_init(&cv, NULL);

	pthread_t ids[N];
	for (int i = 0; i < N; i++)
		pthread_create(&ids[i], NULL, calc, (void *) i);
}
