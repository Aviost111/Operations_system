CC = gcc


all: myzip myunzip

myzip: myzip.c
	$(CC) -o myzip myzip.c


myunzip: myunzip.c
	$(CC) -o myunzip myunzip.c

.PHONY: clean all

clean:
	rm -f myunzip myzip *.gpg
