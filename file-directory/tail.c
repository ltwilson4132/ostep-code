#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

int main(int argc, char* argv[]) {
    if (argc != 3 ) {
        fprintf(stderr, "Usage: %s -n num_lines file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num_lines = atoi(argv[1]);
    if (num_lines <= 0) {
        fprintf(stderr, "Invalid number of lines: %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    FILE* file = fopen(argv[3], "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // seek to near the end of the file
    if (fseek(file, 0L, SEEK_END) != 0) {
        perror("fseek");
        exit(EXIT_FAILURE);
    }

    long pos = ftell(file);
    int lines = 0;
    char line[MAX_LINE_LENGTH];
    int line_length;

    // go backwards until we find the requested number of lines
    while (pos > 0 && lines < num_lines) {
        // read a block of data
        if (pos - MAX_LINE_LENGTH >= 0) {
            pos -= MAX_LINE_LENGTH;
            line_length = MAX_LINE_LENGTH;
        } else {
            line_length = pos;
            pos = 0;
        }
        if (fseek(file, pos, SEEK_SET) != 0) {
            perror("fseek");
            exit(EXIT_FAILURE);
        }
        fread(line, line_length, 1, file);

        // count the number of lines in the block
        char* p = line + line_length - 1;
        while (p >= line) {
            if (*p == '\n') {
                lines++;
                if (lines == num_lines) {
                    break;
                }
            }
            p--;
        }
    }

    // print out the requested lines
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
    exit(EXIT_SUCCESS);
}
