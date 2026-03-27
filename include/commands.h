#ifndef COMMANDS_H
#define COMMANDS_H

void help_view(void);
void new_project(const char *name, int no_include);
void init_project(int no_include);
void build_project(void);
void clean_project(void);
void clean_all(void);

#endif
