#include <stdio.h>
#include <pthread.h>
// remember to set compilation option -pthread

void *worker(void *ptr) {
    // ptr will point to "Hi"
    puts("Hello World");
    return NULL;
}
int main() {
    void *result;
    pthread_t tid1, tid2;
    
    // Start the workers
    pthread_create(&tid1, NULL, worker, "Hi");
    pthread_create(&tid2, NULL, worker, "Jabberwocky");
    
    // Wait for the workers to finish. If you comment this line nothing
    // will be printed
    pthread_join(tid1, &result);
    pthread_join(tid2, &result);
    
    // We can also use pthread_exit(NULL);
    // pthread_exit(NULL)
    
    getchar();
    return 0;
}