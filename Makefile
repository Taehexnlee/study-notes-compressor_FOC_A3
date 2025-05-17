# Makefile
CC = gcc
CFLAGS = -Wall -Werror -std=c99
OBJS = src/main.o src/rle.o src/crypto.o src/fileio.o

notes: $(OBJS)
	$(CC) $(CFLAGS) -o notes $(OBJS)

clean:
	rm -f src/*.o notes