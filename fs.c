//
// Created by dondish on 7/10/18.
//

#include "fs.h"

#include <fuse.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

/**
 * gets the attribute of the file
 * @param path - path to file
 * @param st - the struct to fill
 * @return
 */
static int do_getattr(const char *path, struct stat *st) {
    printf("[LOG] [Filesystem call] [getattr] path: %s", path);
    st->st_uid = getuid();
    st->st_gid = getgid();
    st->st_atime = time(NULL);
    if (strlen(path) > 1 && !strcmp(path + strlen(path) - 1, "/")) {
        st->st_mode = st->st_mode | S_IFDIR;
    } else {
        st->st_mode = st->st_mode | S_IFREG;
    }
    return 0;
}
static int do_mknod(const char *path, mode_t mode, dev_t dev) {

}