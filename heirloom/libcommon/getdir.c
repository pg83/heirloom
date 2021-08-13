#include "getdir.h"

#include <err.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct getdb* getdb_alloc(const char* path, int fd) {
    return (struct getdb*)fdopendir(dup(fd));
}

void getdb_free(struct getdb* db) {
    if (closedir((DIR*)db)) {
        err(-1, "closedir");
    }
}

// intentional memory leak here
struct direc* getdir(struct getdb* db, int* error) {
    struct dirent* ent;
    struct direc* res;

    *error = 0;
    errno = 0;
    ent = readdir((DIR*)db);

    if (!ent) {
        *error = errno;

        return NULL;
    }

    res = (struct direc*)malloc(sizeof(*res));

    if (!res) {
        err(-1, "malloc");
    }

    res->d_ino = ent->d_ino;
    res->d_name = strdup(ent->d_name);

    if (!res->d_name) {
        err(-1, "strdup");
    }

    return res;
}
