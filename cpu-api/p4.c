#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int rc = fork();
    int item;
    char* myargs[1];

    item = (int)argv[1];
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
	    // child: redirect standard output to a file
        myargs[0] = strdup("ls");
        switch(item){
            case 1:
                execl("ls", myargs);
            case 2:
                //execle("/bin/ls", "-la");
            case 3:
                //execlp("/bin/ls", "-la");
            case 4:
                //execv("/bin/ls", "-la");
            case 5:
                //execvp("/bin/ls", "-la");
            case 6:
                //execvpe("/bin/ls", "-la");
            default:
                printf("Invalid argument");
        }
    } else {
        // parent goes down this path (original process)

    }
    return 0;
}
