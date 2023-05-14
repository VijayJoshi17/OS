#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    FILE *fp;
    char buf[BUF_SIZE];
    size_t bytes;

    // Check if at least one argument is passed
    if (argc < 2) {
        printf("Usage: %s [file1] [file2] ...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Loop through all the files
    for (int i = 1; i < argc; i++) {
        // Open the file
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("Error: Unable to open file %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }

        // Read and print the contents of the file
        while ((bytes = fread(buf, 1, BUF_SIZE, fp)) > 0) {
            fwrite(buf, 1, bytes, stdout);
        }

        // Close the file
        fclose(fp);
    }

    return 0;
}
