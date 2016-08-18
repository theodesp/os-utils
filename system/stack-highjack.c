#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Each thread uses a stack memory. The stack 'grows downwards' - if a function calls another function, 
// then the stack is extended to smaller memory addresses. Stack memory includes non-static automatic 
// (temporary) variables, parameter values and the return address. If a buffer is too small some data 
// (e.g. input values from the user), then there is a real possibility that other stack variables 
// and even the return address will be overwritten. 
// The precise layout of the stack's contents and order of the automatic variables is architecture 
// and compiler dependent.


void escape() {
    puts("Welcome. Escape to a shell...");
    system("/bin/sh");
}
void input() {
  void *p; // lea -0x8(&rbp), %rax 
  printf("Address of stack variable: %p\n", &p);
  printf("Something that looks like a return address on stack: %p\n", *((&p)+2));
  // Let's change it to point to the start of our sneaky function.
  ((&p)+2) = escape;
}

int main() {
    printf("main() code starts at %p\n",main);

    input();
    while (1) {
        puts("Hello");
        sleep(1);
    }

    return 0;
}