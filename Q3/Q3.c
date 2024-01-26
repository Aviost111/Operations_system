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

int encode(char *textin, char *textout, long len, void *codec) {
    // Check for invalid input parameters
    if (textin == NULL || textout == NULL || codec == NULL || len <= 0) {
        return -1; // Invalid input parameters
    }

    int count = 0;
    Codec *c = (Codec *) codec;

    // Iterate through each character in the input text
    for (long i = 0; i < len; i++) {
        char ch = textin[i];
        char encodedChar;

        // Encode the character based on its type
        if (ch >= 'a' && ch <= 'z') {
            encodedChar = c->key[ch - 'a'];
            count++;
        } else if (ch >= 'A' && ch <= 'Z') {
            encodedChar = c->key[ch - 'A' + 26];
            count++;
        } else if (ch >= '0' && ch <= '9') {
            encodedChar = c->key[ch - '0' + 51];
            count++;
        } else {
            encodedChar = ch; // Non-alphanumeric characters remain unchanged
        }

        // Store the encoded character in the output text
        textout[i] = encodedChar;
    }

    return count; // Return the number of characters encoded
}


int decode(char *textin, char *textout, long len, void *codec) {
    // Check for invalid input parameters
    if (textin == NULL || textout == NULL || codec == NULL || len <= 0) {
        return -1; // Invalid input parameters
    }

    int count = 0;
    Codec *c = (Codec *) codec;

    // Iterate through each character in the input text
    for (long i = 0; i < len; i++) {
        char ch = textin[i];

        // Search for the character in the key string
        int j = 0;
        while (j < 62 && ch != c->key[j]) {
            j++;
        }

        // Check if a match was found
        if (j < 62) {
            // Found a match, decode the character
            if (j < 26) {
                textout[i] = 'a' + j;  // Lowercase letters
            } else if (j < 52) {
                textout[i] = 'A' + j - 26;  // Uppercase letters
            } else {
                textout[i] = '0' + j - 51;  // Digits
            }
            count++;
        } else {
            // If no match found in the key, keep the original character
            textout[i] = ch;
        }
    }
    return count; // Return the number of characters decoded
}


void freeCodec(void *codec) {
    free(codec);
}