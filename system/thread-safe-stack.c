#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// remember to set compilation option -pthread

// Warning no underflow or overflow checks!
#define COUNT 10
int count;
double values[COUNT];
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; // Single lock to rule them all!

void push(double v) { 
    pthread_mutex_lock(&m); 
    values[count++] = v;
    pthread_mutex_unlock(&m);
}

double pop() {
    pthread_mutex_lock(&m);
    double v = values[--count];
    pthread_mutex_unlock(&m);
    
    return v;
}
int is_empty() {
    pthread_mutex_lock(&m);
    int result= count == 0;
    pthread_mutex_unlock(&m);
    
    return result;
}


// Support for multiple stacks (each one has a mutex)
typedef struct stack {
    int count;
    pthread_mutex_t m; 
    double *values;
} stack_t;

stack_t* stack_create(int capacity) {
    stack_t *result = malloc(sizeof(stack_t));
    result->count = 0;
    result->values = malloc(sizeof(double) * capacity);
    pthread_mutex_init(&result->m, NULL);
    
    return result;
}

void stack_destroy(stack_t *s) {
    free(s->values);
    pthread_mutex_destroy(&s->m);
    free(s);
}

void stack_push(stack_t *s, double v) { 
    pthread_mutex_lock(&s->m); 
    s->values[(s->count)++] = v; 
    pthread_mutex_unlock(&s->m); }

double stack_pop(stack_t *s) { 
    pthread_mutex_lock(&s->m); 
    double v = s->values[--(s->count)]; 
    pthread_mutex_unlock(&s->m); 
  
    return v;
}

int stack_is_empty(stack_t *s) { 
    pthread_mutex_lock(&s->m); 
    int result = s->count == 0; 
    pthread_mutex_unlock(&s->m);

    return result;
}

int main() {
    stack_t *s1 = stack_create(10 /* Max capacity*/);
    stack_t *s2 = stack_create(10);
    stack_push(s1, 3.141);
    stack_push(s2, stack_pop(s1));
    stack_destroy(s2);
    stack_destroy(s1);
}

// Example of a blocking stack
// pthread_mutex_t m= PTHREAD_MUTEX_INITIALIZER; 
// int count = 0;
// double values[10];
// sem_t sitems, sremain;

// void init() {
//   sem_init(&sitems, 0, 0);
//   sem_init(&sremains, 0, 10); // 10 spaces
// }

// double pop() {
//   // Wait until there's at least one item
//   sem_wait(&sitems);

//   pthread_mutex_lock(&m); // CRITICAL SECTION
//   double v= values[--count];
//   pthread_mutex_unlock(&m);

//   sem_post(&sremain); // Hey world, there's at least one space
//   return v;
// }

// void push(double v) {
//   // Wait until there's at least one space
//   sem_wait(&sremain);

//   pthread_mutex_lock(&m); // CRITICAL SECTION
//   values[count++] = v;
//   pthread_mutex_unlock(&m);

//   sem_post(&sitems); // Hey world, there's at least one item
// }