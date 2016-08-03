#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

int func() {
    static int c;    //c = 0, static objects have static storage duration
    int d;          // d = <junk> is an error to assume that it will always be initialized to zero.
    printf("%d %d %d %d\n", a, b, c, d); // Prints 0 0 0 <junk>
    
    // Automatic variables are bound to stack memory only for the lifetime of the function. 
    // After the function returns it is an error to continue to use the memory.
    // So we cannot return &d;
}

void func2() {
    // Heap allocations using malloc are not automatically initialized to zero.
    int* ptr1 = malloc( sizeof(int) );
    
    // Behaves like malloc as the ptr is NULL
    int* ptr2 = realloc(NULL, sizeof(int) ); 
    
    // The function calloc() will allocate a block of memory for an array.
    // During the initialization all bits are set to zero.
    int* ptr3 = calloc( 1, sizeof(int) );
    int* ptr4 = calloc( sizeof(int) , 1);
                                         

    printf("%d %d %d %d\n",*ptr1, *ptr2, *ptr3, *ptr4);
    
    free(ptr1);
    free(ptr2);
    free(ptr3);
    free(ptr4);
    
    // It is an error to free the same block of memory twice.
    // free(ptr1);
    
    // Nither pointers to freed memory should not be used.
    // strcpy(ptr1,"World");
}

void func3() {
    // String literals are character arrays stored in the code segment of the 
    // program, which is immutable. Two string literals may share the same space in memory.
    // The strings pointed to by str1 and str2 may actually reside in the same location in memory.
    const char * str1 = "Hello world";
    const char * str2 = "Hello world";
    
    printf("%p %p\n", str1, str2);
    
    // This will not work
    // strcpy(str1, "Will not work");
    
    // Char arrays, however, contain the literal value which has been copied 
    // from the code segment into either the stack or static memory. 
    // These following char arrays do not reside in the same place in memory.
    
    char arr1[] = "Goodbuy World";
    char arr2[] = "Goodbuy World";
    
    printf("%p %p\n", arr1, arr2);
}


int main() {
    func();
    func2();
    func3();
    
    getchar();
    return 0;
}
