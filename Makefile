CC = gcc
CFLAGS = -Wall -Werror -std=c99 -Iinclude
SRC = src
OBJS = $(SRC)/main.o $(SRC)/rle.o $(SRC)/crypto.o $(SRC)/fileio.o $(SRC)/feedback.o
OUT = notes_app

# Default build
$(OUT): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

# Compile each .c file into .o
$(SRC)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Debug mode with -DDEBUG macro enabled
debug: CFLAGS += -DDEBUG
debug: clean $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

# Clean all object files and executable
clean:
	rm -f $(SRC)/*.o $(OUT)