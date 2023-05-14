#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    FILE *source, *dest;
    char buf[BUF_SIZE];
    size_t bytes;

    // Check if correct number of arguments are passed
    if (argc != 3) {
        printf("Usage: %s [source_file] [destination_file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the source file
    source = fopen(argv[1], "rb");
    if (source == NULL) {
        printf("Error: Unable to open source file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Open the destination file
    dest = fopen(argv[2], "wb");
    if (dest == NULL) {
        printf("Error: Unable to open destination file %s\n", argv[2]);
        fclose(source);
        exit(EXIT_FAILURE);
    }

    // Copy the contents of source file to destination file
    while ((bytes = fread(buf, 1, BUF_SIZE, source)) > 0) {
        fwrite(buf, 1, bytes, dest);
    }

    // Close the files
    fclose(source);
    fclose(dest);

    printf("File copied successfully.\n");

    return 0;
}
