CC = gcc

all: bugc buga bugc_with_debugger buga_with_debugger

bugc: bugc.c
	$(CC) -o bugc bugc.c

buga: buga.c
	$(CC) -o buga buga.c


bugc_with_debugger: bugc.c
	$(CC) -g -o bugc_with_debugger bugc.c

buga_with_debugger: buga.c
	$(CC) -g -o buga_with_debugger buga.c

.PHONY: all clean

clean:
	rm -f bugc buga bugc_with_debugger buga_with_debugger
