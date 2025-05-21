CC = gcc
CFLAGS = -Wall -Werror -std=c99 -Iinclude
SRC = src
OBJS = $(SRC)/main.o $(SRC)/rle.o $(SRC)/crypto.o $(SRC)/fileio.o $(SRC)/feedback.o
OUT = notes_app

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

clean:
	rm -f $(SRC)/*.o $(OUT)