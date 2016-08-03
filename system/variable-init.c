#include <stdio.h>


// If an object that has static storage duration is not initialized explicitly, then:
// ----------------------------------------------------------------------------------
// * if it has pointer type, it is initialized to a NULL pointer;
// * if it has arithmetic type, it is initialized to (positive or unsigned) zero;
// * if it is an aggregate, every member is initialized (recursively) according to these rules;
// * if it is a union, the first named member is initialized (recursively) according to these rules.


// There are four types of storage duration.
// -----------------------------------------
// 1. Automatic storage duration. the object is allocated at the beginning of the 
// enclosed code block and de-allocated at the end. All local objects have this storage 
// duration, except those declared static, extern or thread_local.
//
// 2. Static storage duration. The storage for object is allocated when the program 
// begins and de allocated when the program ends. Only the instance of the object exists. 
//
// 3. thread storage duration. the object allocated when the thread begins and de
// allocated when the thread ends. Each thread has its own instance of object. 
// Only objects declared thread_local have this storage duration. 
//
// 4. Dynamic storage duration. The object is allocated and deallocated per request 
// by using dynamic memory allocation function.


// Global and static variables are stored in the Data Segment (DS) when 
// initialized and block start by symbol (BSS)` when uninitialized.

// These variables have a fixed memory location, and memory is allocated at compile time.

// Thus global and static variables have '0' as their default values.
// Whereas auto variables are stored on the stack, and they do not have a fixed memory location.

// Memory is allocated to auto variables at runtime, but not at compile time. 
// Hence auto variables have their default value as garbage.

int a;          //a = 0, global objects have static storage duration
static int b;   //b = 0, global static objects have static storage duration

void func() {
    static int c;    //c = 0, static objects have static storage duration
    int d;          // d = 0 local objects are not always init to default values
    printf("%d %d %d %d\n", a, b, c, d); // Prints 0 0 0 <junk>
}

int main() {
    func();
    
    getchar();
    return 0;
}
