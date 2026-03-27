#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "commands.h"
#include "build.h"
#include "utils.h"

void help_view(void) {
    printf("lxt - project manager\n\n");

    printf("Usage:\n");
    printf("  lxt <command> --options\n\n");

    printf("Commands:\n");
    printf("  help                     Show this message\n");
    printf("  new <name> [--no-include] Create new project\n");
    printf("  init [--no-include]      Init project in current directory\n");
    printf("  build                    Build project using make\n");
    printf("  clean                    Remove build files\n");
    printf("  clean --all              Remove ALL project files\n\n");

    printf("Options:\n");
    printf("  --no-include             Do not create include/ directory\n\n");

    printf("Examples:\n");
    printf("  lxt new myproj\n");
    printf("  lxt new myproj --no-include\n");
    printf("  lxt init\n");
    printf("  lxt build\n");
    printf("  lxt clean\n");
    printf("  lxt clean --all\n");
}

static void create_structure(int no_include) {
    mkdir("src", 0755);
    if (!no_include) {
        mkdir("include", 0755);
    }
    create_makefile(no_include);
}

void new_project(const char *name, int no_include) {
    if (mkdir(name, 0755) != 0) {
        perror("mkdir");
        return;
    }

    if (chdir(name) != 0) {
        perror("chdir");
        return;
    }

    create_structure(no_include);
    printf("Project '%s' created\n", name);
}

void init_project(int no_include) {
    create_structure(no_include);
    printf("Project initialized\n");
}

void build_project(void) {
    execlp("make", "make", NULL);
    perror("execlp");
}

void clean_project(void) {
    remove("bin/app");
    remove_directory("build");
    printf("Clean done\n");
}

void clean_all(void) {
    remove_directory("build");
    remove_directory("bin");
    remove_directory("src");
    remove_directory("include");
    remove("Makefile");
    printf("Full clean done\n");
}
