CC ?= gcc
CFLAGS = -Wall
BIN_DIR = ./bin

run:
	${CC} src/main.c lib/src/glad.c src/world/*.c src/objects/*.c -Ilib $(CFLAGS) -o $(BIN_DIR)/main -ldl -lglfw -lm
	$(BIN_DIR)/main

debug:
	${CC} src/main.c -g lib/src/glad.c src/world/*.c src/objects/*.c -Ilib $(CFLAGS) -o $(BIN_DIR)/main -ldl -lglfw -lm
	valgrind --track-origins=yes $(BIN_DIR)/main
lines:
	find . -name "*.c" -not -path "./lib*" -o -name "*.h"  -not -path "./lib*" | xargs wc -l