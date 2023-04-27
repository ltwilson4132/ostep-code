#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

//In this examples, both processes are able to write to the file.
//The parent is able to write it's entire string to the file before the
//child writes it's string to the file.
int
main(int argc, char *argv[])
{
    int rc, fd;
    size_t nbytes;
    char out[255];
    fd = open("test.txt", O_RDWR);
    rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        strcpy(out, "I'm the child and I just wanted to say hi.");
        nbytes = strlen(out);
        printf("Child is writing the string \"%s\" to the file.\n", out);
        write(fd, out, nbytes);
    } else {
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d)\n", rc, (int) getpid());
        strcpy(out, "I'm the parent and I am here to supervise my child.");
        nbytes = strlen(out);
        printf("Parent is writing the string \"%s\" to the file.\n", out);
        write(fd, out, nbytes);
    }
    return 0;
}
