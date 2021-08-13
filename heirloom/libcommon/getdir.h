#pragma once

struct direc {
    unsigned long long d_ino;
    char* d_name;
};

extern struct getdb* getdb_alloc(const char*db, int fd);
extern void getdb_free(struct getdb* db);
extern struct direc* getdir(struct getdb* db, int* err);
