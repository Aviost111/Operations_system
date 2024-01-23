#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[62];
} Codec;

void *createCodec(char key[62]) {
    // Check if the key is valid (no duplicate mappings)
    for (int i = 0; i < 62; i++) {
        for (int j = i + 1; j < 62; j++) {
            if (key[i] == key[j]) {
                return NULL; // Invalid key
            }
        }
    }

    Codec *codec = (Codec *) malloc(sizeof(Codec));
    if (codec == NULL) {
        return NULL; // Memory allocation error
    }

    strcpy(codec->key, key);
    return codec;
}

int encode(char *textin, char *textout, int len, void *codec) {
    if (textin == NULL || textout == NULL || codec == NULL) {
        return -1; // Invalid input parameters
    }

    int count = 0;
    Codec *c = (Codec *) codec;

    for (int i = 0; i < len; i++) {
        char ch = textin[i];
        if (ch >= 'a' && ch <= 'z') {
            textout[i] = c->key[ch - 'a'];
            count += 1;
        } else if (ch >= 'A' && ch <= 'Z') {
            textout[i] = c->key[ch - 'A' + 26];
            count += 1;
        } else if (ch >= '0' && ch <= '9') {
            textout[i] = c->key[ch - '0' + 52];
            count += 1;
        } else {
            textout[i] = ch; // Non-alphanumeric characters remain unchanged
        }
    }

    return count;
}

int decode(char *textin, char *textout, int len, void *codec) {
    if (textin == NULL || textout == NULL || codec == NULL) {
        return -1; // Invalid input parameters
    }

    int count = 0;
    Codec *c = (Codec *) codec;
    for (int i = 0; i < len; i++) {
        char ch = textin[i];
        if (ch >= 'a' && ch <= 'z') {
            textout[i] = strchr(c->key, ch) - c->key + 'a';
            count += 1;
        } else if (ch >= 'A' && ch <= 'Z') {
            textout[i] = strchr(c->key, ch) - c->key + 'A' - 26;
            count += 1;
        } else if (ch >= '0' && ch <= '9') {
            textout[i] = strchr(c->key, ch) - c->key + '0' - 52;
            count += 1;
        } else {
            textout[i] = ch; // Non-alphanumeric characters remain unchanged
        }
    }

    return count;
}

void freeCodec(void *codec) {
    free(codec);
}