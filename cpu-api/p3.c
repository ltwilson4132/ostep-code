#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    //printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("Child process (pid:%d) says hello.\n", (int) getpid());
    } else {
        // parent goes down this path (original process)
        //Not the best way, but the parent goes to sleep long enough for 
        //the child to finish.
        sleep(1);
        //wait(NULL);
        printf("Parent process (pid:%d) say goodbye.\n", (int) getpid());
    }
    return 0;
}
