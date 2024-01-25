CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET1 = encode
TARGET2 = decode

all: $(TARGET1) $(TARGET2)

$(TARGET1): Main_Encode.o Q3.o
	$(CC) $(CFLAGS) -o $(TARGET1) Main_Encode.o Q3.o

$(TARGET2): Main_Decode.o Q3.o
	$(CC) $(CFLAGS) -o $(TARGET2) Main_Decode.o Q3.o

Main_Decode.o: Main_Decode.c Q3.h
	$(CC) $(CFLAGS) -c Main_Decode.c

Main_Encode.o: Main_Encode.c Q3.h
	$(CC) $(CFLAGS) -c Main_Encode.c

Q3.o: Q3.c Q3.h
	$(CC) $(CFLAGS) -c Q3.c

.PHONY: clean all

clean:
	rm -f $(TARGET1) *.o $(TARGET2) *.o
