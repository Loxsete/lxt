#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "commands.h"
#include "build.h"
#include "utils.h"

static void create_template(const char *lang) {
    if (!lang) return;

    FILE *f = fopen("src/main.c", "w");
    if (!f) {
        perror("fopen");
        return;
    }

    if (strcmp(lang, "c") == 0) {
        fprintf(f, "#include <stdio.h>\n\n");
        fprintf(f, "int main(int argc, char *argv[]) {\n");
        fprintf(f, "    return 0;\n");
        fprintf(f, "}\n");
    } else if (strcmp(lang, "cpp") == 0) {
        fprintf(f, "#include <iostream>\n\n");
        fprintf(f, "int main(int argc, char *argv[]) {\n");
        fprintf(f, "    return 0;\n");
        fprintf(f, "}\n");
    } else {
        printf("Unknown template: %s\n", lang);
    }

    fclose(f);
}

static void create_structure(int no_include, const char *tmpl) {
    mkdir("src", 0755);
    if (!no_include)
        mkdir("include", 0755);
    create_makefile(no_include);
    create_template(tmpl);
}

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
    printf("  clean --all              Remove ALL project files\n");
    printf("  run                      Build and run project\n\n");

    printf("Options:\n");
    printf("  --no-include             Do not create include/ directory\n");
    printf("  --template <lang>        Generate main file (c, cpp)\n\n");

    printf("Examples:\n");
    printf("  lxt new myproj\n");
    printf("  lxt new myproj --no-include\n");
    printf("  lxt new myproj --template c\n");
    printf("  lxt new myproj --template cpp\n");
    printf("  lxt init\n");
    printf("  lxt build\n");
    printf("  lxt run\n");
    printf("  lxt clean\n");
    printf("  lxt clean --all\n");
}

void new_project(const char *name, int no_include, const char *tmpl) {
    if (mkdir(name, 0755) != 0) {
        perror("mkdir");
        return;
    }

    if (chdir(name) != 0) {
        perror("chdir");
        return;
    }

    create_structure(no_include, tmpl);
    printf("Project '%s' created\n", name);
}

void init_project(int no_include, const char *tmpl) {
    create_structure(no_include, tmpl);
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

void run_project(int argc, char *argv[]) {
    pid_t pid = fork();

    if (pid == 0) {
        execlp("make", "make", NULL);
        perror("make");
        exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            execv("./bin/app", argv);
            perror("run");
        } else {
            printf("Build failed\n");
        }
    } else {
        perror("fork");
    }
}
