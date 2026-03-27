#ifndef COMMANDS_H
#define COMMANDS_H

void help_view(void);
void new_project(const char *name, int no_include, const char *tmpl);
void init_project(int no_include, const char *tmpl);
void build_project(void);
void clean_project(void);
void clean_all(void);
void run_project(int argc, char *argv[]);

#endif
