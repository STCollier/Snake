CC ?= gcc
CFLAGS = -Wall
BIN_DIR = ./bin

run:
	${CC} src/main.c lib/src/glad.c src/include/*.c -Ilib -Isrc/gfx $(CFLAGS) -o $(BIN_DIR)/main -ldl -lglfw -lm
	$(BIN_DIR)/main