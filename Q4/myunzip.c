#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024


void myunzip(char* file) {
    // Decrypt the file
    if (fork() == 0) {
        // Child process: Execute gpg command for decryption
        execlp("gpg", "gpg", "--decrypt", file, NULL);
        perror("execlp");
        exit(1);
    } else {
        // Parent process: Wait for the child process to finish
        wait(NULL);
    }

    // Decompress the file
    char decompressed_file[64];
    snprintf(decompressed_file, sizeof(decompressed_file), "%s.tar", file);

    if (fork() == 0) {
        // Child process: Execute uncompress command
        execlp("uncompress", "uncompress", "-f", file, "-o", decompressed_file, NULL);
        perror("execlp");
        exit(1);
    } else {
        // Parent process: Wait for the child process to finish
        wait(NULL);
    }

    // Extract the archive
    if (fork() == 0) {
        // Child process: Execute tar command for extraction
        execlp("tar", "tar", "-xf", decompressed_file, NULL);
        perror("execlp");
        exit(1);
    } else {
        // Parent process: Wait for the child process to finish
        wait(NULL);
    }

    // Delete temporary file
    unlink(decompressed_file);
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory> (to archive) or <file> (to unzip)\n", argv[0]);
        exit(1);
    }

    // Check if the file or directory exists
    if (access(argv[1], F_OK) != 0) {
        perror("File or directory does not exist");
        exit(1);
    }

    myunzip(argv[1]);

    return 0;
}
