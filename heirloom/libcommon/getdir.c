#include "getdir.h"

#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

struct getdb* getdb_alloc(const char* path, int fd) {
    return (struct getdb*)fdopendir(dup(fd));
}

void getdb_free(struct getdb* db) {
    closedir((DIR*)db);
}

struct direc* getdir(struct getdb* db, int* err) {
    struct dirent* ent;
    struct direc* res;

    *err = 0;

    ent = readdir((DIR*)db);

    if (!ent) {
        *err = errno;

        return NULL;
    }

    res = (struct direc*)malloc(sizeof(*res));

    if (!res) {
        *err = ENOMEM;

        return NULL;
    }

    res->d_ino = ent->d_ino;
    res->d_name = ent->d_name;

    return res;
}
