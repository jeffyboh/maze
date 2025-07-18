CC = gcc
TARGET = maze
BIN_DIR = bin
SRC = maze.c
LIBS = ncurses

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(SRC)
	$(CC) $(SRC) -g -o $@ -l$(LIBS)


clean:
	rm -rf $(BIN_DIR)/$(TARGET)


