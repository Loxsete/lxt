#include <stdio.h>
#include <string.h>
#include "commands.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Run lxt help\n");
        return 1;
    }

    if (strcmp(argv[1], "help") == 0) {
        help_view();
        return 0;
    }

    if (strcmp(argv[1], "new") == 0) {
        if (argc < 3) { printf("Usage: lxt new <name> [--no-include] [--template <lang>]\n"); return 1; }
    
        const char *name = argv[2];
        int no_include = 0;
        const char *tmpl = NULL;
    
        for (int i = 3; i < argc; i++) {
            if (strcmp(argv[i], "--no-include") == 0) {
                no_include = 1;
            } else if (strcmp(argv[i], "--template") == 0 && i + 1 < argc) {
                tmpl = argv[++i];
            }
        }
    
        new_project(name, no_include, tmpl);
        return 0;
    }
    
    if (strcmp(argv[1], "init") == 0) {
        int no_include = 0;
        const char *tmpl = NULL;
    
        for (int i = 2; i < argc; i++) {
            if (strcmp(argv[i], "--no-include") == 0) {
                no_include = 1;
            } else if (strcmp(argv[i], "--template") == 0 && i + 1 < argc) {
                tmpl = argv[++i];
            }
        }
    
        init_project(no_include, tmpl);
        return 0;
    }

    if (strcmp(argv[1], "build") == 0) {
        build_project();
    }

	if (strcmp(argv[1], "run") == 0) {
        run_project(argc, argv);
        return 0;
    }

    if (strcmp(argv[1], "clean") == 0) {
        int all = 0;

        for (int i = 2; i < argc; i++) {
            if (strcmp(argv[i], "--all") == 0) {
                all = 1;
            }
        }

        if (all)
            clean_all();
        else
            clean_project();
        return 0;
    }

    printf("Unknown command: %s\n", argv[1]);
    return 1;
}
