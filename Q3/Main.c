#include "Q3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <src_file> <dst_file>\n", argv[0]);
        return 1;
    }

    FILE *src_file = fopen(argv[2], "r");
    FILE *dst_file = fopen(argv[3], "w");

    if (src_file == NULL || dst_file == NULL) {
        perror("Error opening files");
        return 1;
    }

    char key[62] = "defghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abc";
    void *codec = createCodec(key);

    if (codec == NULL) {
        fprintf(stderr, "Invalid key\n");
        return 1;
    }

    fseek(src_file, 0, SEEK_END);
    long len = ftell(src_file);
    fseek(src_file, 0, SEEK_SET);

    char *textin = (char *) malloc(len);
    char *textout = (char *) malloc(len);

    fread(textin, 1, len, src_file);

    int result = encode(textin, textout, len, codec);

    if (result != -1) {
        fwrite(textout, 1, result, dst_file);
    } else {
        fprintf(stderr, "Encoding error\n");
    }

    fclose(src_file);
    fclose(dst_file);
    free(textin);
    free(textout);
    freeCodec(codec);

    return 0;
}