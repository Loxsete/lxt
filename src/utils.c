#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"

int remove_directory(const char *path) {
    DIR *d = opendir(path);
    struct dirent *entry;
    char fullpath[1024];

    if (!d) return -1;

    while ((entry = readdir(d)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(fullpath, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                remove_directory(fullpath);
            } else {
                remove(fullpath);
            }
        }
    }
    closedir(d);
    return rmdir(path);
}
