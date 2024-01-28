#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {

    // Check for correct number of arguments
    if (argc != 2) {
        printf("Usage: %s <file_to_compress>\n", argv[0]);
        exit(1);
    }

    // Determine file type and adjust tar command accordingly
    char *file_extension = strrchr(argv[1], '.');
    char *tar_args[5];  // Declare tar_args array

    if (strcmp(file_extension, ".tar") == 0) {
        // Already a tar archive, extract it
        tar_args[0] = "tar";
        tar_args[1] = "xf";
        tar_args[2] = "-";  // Read from stdin
        tar_args[3] = NULL;
    } else {
        tar_args[0] = "tar";
        tar_args[1] = "cf";
        tar_args[2] = "-";  // Output to stdout
        tar_args[3] = argv[1];  // Directory to archive
        tar_args[4] = NULL;
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

    // Child process 1: tar
    pid = fork();
    if (pid == 0) {
        close(1);  // Close stdout
        dup2(pipefd1[1], 1);  // Redirect stdout to pipefd1[1]
        close(pipefd1[0]);  // Close unused read end
        close(pipefd2[0]);  // Close unused pipes
        close(pipefd2[1]);

        execvp("/bin/tar", tar_args);
        perror("execvp tar");
        exit(1);
    }

    // Child process 2: gzip
    pid = fork();
    if (pid == 0) {
        close(0);  // Close stdin
        close(1);  // Close stdout
        dup2(pipefd1[0], 0);  // Redirect stdin to pipefd1[0]
        dup2(pipefd2[1], 1);  // Redirect stdout to pipefd2[1]
        close(pipefd1[1]);  // Close unused write end
        close(pipefd2[0]);  // Close unused read end

        char *gzip_args[] = {"gzip", "-9", NULL};
        execvp("/bin/gzip", gzip_args);
        perror("execvp gzip");
        exit(1);
    }

    // Child process 3: gpg
    pid = fork();
    if (pid == 0) {
        close(0);  // Close stdin
        dup2(pipefd2[0], 0);  // Redirect stdin to pipefd2[0]
        close(pipefd1[0]);  // Close unused pipes
        close(pipefd1[1]);
        close(pipefd2[1]);

        char *gpg_args[] = {"gpg", "-c", "-o", "compressed.tar.gz.gpg", NULL};
        execvp("/bin/gpg", gpg_args);
        perror("execvp gpg");
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

    printf("Compression completed, terminating\n");

    return 0;
}