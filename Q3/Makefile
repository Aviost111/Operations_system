CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET1 = encode
TARGET2 = decode

all: $(TARGET1) $(TARGET2)

$(TARGET1): Main_Encode.o encriptor.o
	$(CC) $(CFLAGS) -o $(TARGET1) Main_Encode.o encriptor.o

$(TARGET2): Main_Decode.o encriptor.o
	$(CC) $(CFLAGS) -o $(TARGET2) Main_Decode.o encriptor.o

Main_Decode.o: Main_Decode.c encriptor.h
	$(CC) $(CFLAGS) -c Main_Decode.c

Main_Encode.o: Main_Encode.c encriptor.h
	$(CC) $(CFLAGS) -c Main_Encode.c

encriptor.o: encriptor.c encriptor.h
	$(CC) $(CFLAGS) -c encriptor.c

.PHONY: clean all

clean:
	rm -f $(TARGET1) *.o $(TARGET2) *.o
