#include <stdio.h>
#include "build.h"

void create_makefile(int no_include) {
    FILE *f = fopen("Makefile", "w");

    if (!f) {
        perror("fopen");
        return;
    }

    fprintf(f, "CC = gcc\n");

    if (!no_include)
        fprintf(f, "CFLAGS = -Iinclude\n\n");
    else
        fprintf(f, "CFLAGS = \n\n");

    fprintf(f, "SRC = $(wildcard src/*.c)\n");
    fprintf(f, "OBJ = $(SRC:src/%%.c=build/%%.o)\n\n");

    fprintf(f, "all: bin/app\n\n");

    fprintf(f, "bin/app: $(OBJ)\n");
    fprintf(f, "\tmkdir -p bin\n");
    fprintf(f, "\t$(CC) $(OBJ) -o bin/app\n\n");

    fprintf(f, "build/%%.o: src/%%.c\n");
    fprintf(f, "\tmkdir -p build\n");
    fprintf(f, "\t$(CC) $(CFLAGS) -c $< -o $@\n\n");

    fprintf(f, "clean:\n");
    fprintf(f, "\trm -rf build bin/app\n");

    fclose(f);
}
