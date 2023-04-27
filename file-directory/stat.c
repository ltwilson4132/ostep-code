#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void
main(int argc, char *argv[])
{
    struct stat buf;
    
    if(argc != 2){
        fprintf(stderr, "Incorrect number of arguments\n");
        exit(1);
    }

    if(stat(argv[1], &buf) == -1){
        perror("stat");
        exit(1);
    }
    //Inode number
    printf("I-node number:\t\t\t%ld\n", (long) buf.st_ino);

    //File size
    printf("File size:\t\t\t%lld bytes\n", (long long) buf.st_size);

    //Number of blocks allocated
    printf("Number of Blocks Allocated:\t%lld\n", (long long) buf.st_blocks);

    //Reference count
    printf("Link count:\t\t\t%ld\n", (long) buf.st_nlink);

    //Last file access
    printf("Last file access:\t\t%s", ctime(&buf.st_atime));

    //Last modified
    printf("Last file modification:\t\t%s", ctime(&buf.st_mtime));

    exit(0);
}
