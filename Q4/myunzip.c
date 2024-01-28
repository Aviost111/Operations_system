#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int myunzip(char *file) {
    char tmp_template[] = "./archive.XXXXXX";
    int tmp_fd = mkstemp(tmp_template);

    if (tmp_fd == -1) {
        perror("mkstemp");
        exit(1);
    }

    FILE *tmp_file = fdopen(tmp_fd, "w+");
    if (!tmp_file) {
        perror("fdopen");
        exit(1);
    }

    pid_t pid = fork();

    if (pid == 0) {
        execlp("gpg", "gpg", "-d", file , NULL);
        perror("gpg");
        exit(1);
    } else {
        wait(NULL);
    }

    rewind(tmp_file);

    pid = fork();

    if (pid == 0) {
        execlp("gunzip", "gunzip", "-c", tmp_template, NULL);
        perror("gunzip");
        exit(1);
    } else {
        wait(NULL);
    }

    rewind(tmp_file);

    pid = fork();

    if (pid == 0) {
        execlp("tar", "tar", "xf","-f", "-", NULL);
        perror("tar");
        exit(1);
    } else {
        wait(NULL);
    }

    fclose(tmp_file);
    unlink(tmp_template);

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];

    // Validate file
    if (access(filename, F_OK) != 0) {
        printf("Error: File %s does not exist\n", filename);
        exit(1);
    }

    if (access(filename, R_OK) != 0) {
        printf("Error: No read permissions for %s\n", filename);
        exit(1);
    }

    // Call myunzip
    int status = myunzip(filename);

    if (status == 0) {
        printf("Archive extracted successfully\n");
    } else {
        printf("Error extracting archive\n");
    }

    return 0;
}
