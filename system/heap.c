#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// brk() sets the end of the data segment to the value specified by addr, 
// when that value is reasonable, the system has enough memory, 
// and the process does not exceed its maximum data size.

// sbrk() increments the program's data space by increment bytes. 
// Calling sbrk() with an increment of 0 can be used to find the 
// current location of the program break.


void escape() {
    puts("Welcome. Escape to a shell...");
    system("/bin/sh");
}
void input() {
  void *p;
  printf("Address of stack variable: %p\n", &p);
  printf("Something that looks like a return address on stack: %p\n", *((&p)+2));
  // Let's change it to point to the start of our sneaky function.
  *((&p)+2) = escape;
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