#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

int myzip(char* dir) {
    char tmp_template[] = "./archive.XXXXXX";
    int tmp_fd = mkstemp(tmp_template);

    if (tmp_fd == -1) {
        perror("mkstemp");
        exit(1);
    }

    FILE* tmp_file = fdopen(tmp_fd, "w+");
    if (!tmp_file) {
        perror("fdopen");
        exit(1);
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child process: Execute tar command to archive the directory and write to the temporary file
        dup2(fileno(tmp_file), STDOUT_FILENO);  // Redirect stdout to the temporary file
        execlp("tar", "tar", "cf", "-", dir, NULL);
        perror("tar");
        exit(1);
    } else {
        // Parent process: Wait for the child process to finish
        wait(NULL);
    }

    // Rewind the temporary file pointer to the beginning
    rewind(tmp_file);

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid == 0) {
        // Child process: Execute compress command, reading from the temporary file
        close(pipe_fd[0]);  // Close the read end of the pipe
        dup2(fileno(tmp_file), STDIN_FILENO);  // Redirect stdin to the temporary file
        dup2(pipe_fd[1], STDOUT_FILENO);  // Redirect stdout to the write end of the pipe
        execlp("gzip", "gzip", "-c", "-", NULL);
        perror("compress");
        exit(1);
    } else {
        // Parent process: Wait for the child process to finish
        wait(NULL);
        close(pipe_fd[1]);  // Close the write end of the pipe

        // Rewind the temporary file pointer to the beginning
        rewind(tmp_file);

        // Read from the pipe and write to the temporary file
        char buffer[1024];
        ssize_t bytesRead;

        while ((bytesRead = read(pipe_fd[0], buffer, sizeof(buffer))) > 0) {
            fwrite(buffer, 1, bytesRead, tmp_file);
        }

        close(pipe_fd[0]);  // Close the read end of the pipe
    }

    // Rewind the temporary file pointer to the beginning
    rewind(tmp_file);

    pid = fork();

    if (pid == 0) {
        // Child process: Execute gpg command to encrypt the temporary file
        execlp("gpg", "gpg", "-c", tmp_template, NULL);
        perror("gpg");
        exit(1);
    } else {
        // Parent process: Wait for the child process to finish
        wait(NULL);
    }

    fclose(tmp_file);
    unlink(tmp_template);

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        exit(1);
    }

    char *directory = argv[1];

    // Validate directory
    if (access(directory, F_OK) != 0) {
        printf("Error: Directory %s does not exist\n", directory);
        exit(1);
    }

    // Call myzip
    int status = myzip(directory);

    if (status == 0) {
        printf("Directory archived successfully\n");
    } else {
        printf("Error archiving directory\n");
    }

    return 0;
}
