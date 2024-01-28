#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

void myzip(char* directory) {
    char temp_file[64];

    // Create temporary file using mktemp
    snprintf(temp_file, sizeof(temp_file), "%s.tar", directory);

    if (mktemp(temp_file) == NULL) {
        perror("mktemp");
        exit(1);
    }

    // Fork a child process
    pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        // Child process: Execute tar command to archive the directory
        char* args[] = {"tar", "-czf", temp_file, "-C", directory, ".", NULL};
        execv("/bin/tar", args);
        perror("execv");
        exit(1);
    } else {
        // Parent process: Wait for the child process to finish

        wait(NULL);

        // Compress the temporary file
        char encrypted_file[64];
        snprintf(encrypted_file, sizeof(encrypted_file), "%s.gz", temp_file);

        if (fork() == 0) {
            // Child process: Execute compress command
            execlp("compress", "compress", "-f", temp_file, "-o", encrypted_file, NULL);
            perror("execlp");
            exit(1);
        } else {
            // Parent process: Wait for the child process to finish
            wait(NULL);
        }

        // Encrypt the compressed file
        if (fork() == 0) {
            // Child process: Execute gpg command for encryption
            execlp("gpg", "gpg", "--symmetric", "-c", encrypted_file, NULL);
            perror("execlp");
            exit(1);
        } else {
            // Parent process: Wait for the child process to finish
            wait(NULL);
        }

        // Delete temporary file
        unlink(temp_file);
    }
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

    myzip(argv[1]);

    return 0;
}
