#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int rc, x = 50;
    printf("The value of x before the fork is %d\n", x);
    rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        // Child process will get a copy of the parent's value of x after the fork. 
        // In this example, the parent and child will both contains x = 50 after the fork.
        printf("Hello, I am child (pid:%d)\nMy value for x after the fork is %d\n", (int) getpid(), x);
        // After this statement, the child contains x = 60
        x += 10;
        printf("The child (pid:%d) now has a value of %d for x.\n", (int) getpid(), x);
    } else {
        // parent goes down this path (original process)
        printf("Hello, I am parent of %d (pid:%d)\nMy value for x after the fork is %d\n", rc, (int) getpid(), x);
        // After this statement, this parent contains x = 55
        x += 5;
        printf("The parent (pid:%d) now has a value of %d for x.\n", (int) getpid(), x);
    }
    return 0;
}
