#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char *argv[])
{
    char *dir_path;
    int lflag = 0;

    // Determine directory path and -l flag
    if (argc == 1) {
        dir_path = ".";
    } else if (argc == 2) {
        if (strcmp(argv[1], "-l") == 0) {
            fprintf(stderr, "Missing directory argument\n");
            exit(1);
        }
        dir_path = argv[1];
    } else if (argc == 3) {
        if (strcmp(argv[1], "-l") == 0) {
            lflag = 1;
            dir_path = argv[2];
        } else {
            fprintf(stderr, "Invalid arguments\n");
            exit(1);
        }
    } else {
        fprintf(stderr, "Invalid arguments\n");
        exit(1);
    }

    // Open directory
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("opendir");
        exit(1);
    }

    // Read directory entries
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Print filename
        printf("%s", entry->d_name);

        // Print file info if -l flag is set
        if (lflag) {
            char path[512];
            struct stat buf;

            // Construct full path
            snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

            // Get file info
            if (stat(path, &buf) == -1) {
                perror("stat");
                exit(1);
            }

            // Print file permissions
            printf(" %04o", buf.st_mode & 0777);

            // Print owner and group names
            struct passwd *pw = getpwuid(buf.st_uid);
            struct group *gr = getgrgid(buf.st_gid);
            if (pw != NULL) {
                printf(" %s", pw->pw_name);
            } else {
                printf(" %d", buf.st_uid);
            }
            if (gr != NULL) {
                printf(" %s", gr->gr_name);
            } else {
                printf(" %d", buf.st_gid);
            }

            // Print file size and modification time
            printf(" %lld %s", (long long) buf.st_size, ctime(&buf.st_mtime));
        }

        printf("\n");
    }

    // Close directory
    closedir(dir);

    return 0;
}
