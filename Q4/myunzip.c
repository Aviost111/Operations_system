#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    // Check for correct number of arguments
    if (argc != 2) {
        printf("Usage: %s <compressed_file>\n", argv[0]);
        exit(1);
    }

    // Phase 2 (pipe-based implementation)
    int pipefd1[2];
    int pipefd2[2];

    if (pipe(pipefd1) == -1) {
        perror("pipe1");
        exit(1);
    }
    if (pipe(pipefd2) == -1) {
        perror("pipe2");
        exit(1);
    }

    pid_t pid;

    // Child process 1: gpg
    pid = fork();
    if (pid == 0) {
        close(1);  // Close stdout
        dup2(pipefd1[1], 1);  // Redirect stdout to pipefd1[1]
        close(pipefd1[0]);  // Close unused read end
        close(pipefd2[0]);  // Close unused pipes
        close(pipefd2[1]);

        char *gpg_args[] = {"gpg", "-d", argv[1], NULL};  // Decrypt the file
        execvp("/bin/gpg", gpg_args);
        perror("execvp gpg");
        exit(1);
    }

    // Child process 2: gunzip
    pid = fork();
    if (pid == 0) {
        close(0);  // Close stdin
        close(1);  // Close stdout
        dup2(pipefd1[0], 0);  // Redirect stdin to pipefd1[0]
        dup2(pipefd2[1], 1);  // Redirect stdout to pipefd2[1]
        close(pipefd1[1]);  // Close unused write end
        close(pipefd2[0]);  // Close unused read end

        char *gunzip_args[] = {"gunzip", "-c", "-", NULL};  // Decompress with gunzip
        execvp("/bin/gunzip", gunzip_args);
        perror("execvp gunzip");
        exit(1);
    }

    // Child process 3: tar
    pid = fork();
    if (pid == 0) {
        close(0);  // Close stdin
        dup2(pipefd2[0], 0);  // Redirect stdin to pipefd2[0]
        close(pipefd1[0]);  // Close unused pipes
        close(pipefd1[1]);
        close(pipefd2[1]);

        char *tar_args[] = {"tar", "xf", "-", NULL};  // Extract the archive
        execvp("/bin/tar", tar_args);
        perror("execvp tar");
        exit(1);
    }

    // Parent process: Wait for children and close pipes
    close(pipefd1[0]);
    close(pipefd1[1]);
    close(pipefd2[0]);
    close(pipefd2[1]);

    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("Decompression completed, terminating\n");

    return 0;
}
