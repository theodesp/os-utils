#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// About forking
// -------------
// The process id returned by getpid(). The parent process id returned by getppid().
// The parent is notified via a signal when the child process finishes but not vice versa.
// The child does not inherit pending signals or timer alarms.

void func() {
    int answer = 86 >> 2;
    printf("Answer: %d", answer);
    
    // Prints Answer twice as there's no newline printed,
    // and we didn't call fflush, or change the buffering mode.
    // Thus the child process starts with a non-empty output buffer 
    // which will be flushed when the program exits.
    fork();
}

int func2() {
    pid_t child_id = fork();
    if (child_id == -1) { perror("fork"); exit(EXIT_FAILURE);}
    
    if (child_id > 0) { 
        // We are in the parent. Wait for the child to finish.
        // This also prevents zombies.
        int status; 
        waitpid( child_id, &status, 0 );
        printf("Exiting from parent...");
        
        return 0;
    } else { 
        // We are in the child. Simulate work
        sleep(2);
        execl("/bin/ls", "ls","-alh", (char *) NULL);

        // If we get to this line, something went wrong!
        perror("exec failed!");
    }
}

int func3(int c, char **v) {
    // Sleepsort
    while (--c > 1 && !fork());
    int val  = atoi(v[c]);
    sleep(val);
    printf("%d\n", val);
    
    return 0;
}


int main(int c, char **v) {
    //func();
    //func2();
    
    
    
    return 0;
}