CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = encode

$(TARGET): Main.o Q3.o
	$(CC) $(CFLAGS) -o $(TARGET) Main.o Q3.o

Main.o: Main.c Q3.h
	$(CC) $(CFLAGS) -c Main.c

Q3.o: Q3.c Q3.h
	$(CC) $(CFLAGS) -c Q3.c

.PHONY: clean

clean:
	rm -f $(TARGET) *.o
