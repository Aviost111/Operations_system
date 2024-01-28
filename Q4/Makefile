CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all = myzip myunzip

myzip: myzip.c
	$(CC) $(CFLAGS) -o myzip myzip.c


myunzip: myunzip.c
	$(CC) $(CFLAGS) -o myunzip myunzip.c

.PHONY: clean all

clean:
	rm -f myunzip myzip
