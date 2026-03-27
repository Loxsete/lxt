CC = gcc
CFLAGS = -Iinclude

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)

all: bin/app

bin/app: $(OBJ)
	mkdir -p bin
	$(CC) $(OBJ) -o bin/app

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build bin/app
