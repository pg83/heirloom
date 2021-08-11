/*
 * Copyright (c) 2003 Gunnar Ritter
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute
 * it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */
/*    Sccsid @(#)getdir.h    1.4 (gritter) 10/19/03    */

#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

#include "getdir.h"

struct getdb* getdb_alloc(const char* path, int fd) {
    return (struct getdb*)fdopendir(fd);
}

void getdb_free(struct getdb* db) {
    closedir((DIR*)db);
}

struct direc* getdir(struct getdb* db, int* err) {
    struct dirent* ent;
    struct direc* res;

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
