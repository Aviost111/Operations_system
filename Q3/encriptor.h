#ifndef OPERATIONS_SYSTEM_ENCRIPTOR_H
#define OPERATIONS_SYSTEM_ENCRIPTOR_H


void *createCodec(char key[62]);
int encode(char *textin, char *textout, long len, void *codec);
int decode(char *textin, char *textout, long len, void *codec);
void freeCodec(void *codec);

#endif