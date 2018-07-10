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

static int do_mknod(const char *path, mode_t mode, dev_t dev) {
    if (S_ISREG(mode)) {  // allow only regular files
        return mknod(path, mode, dev);
    }
    return -1;
}

static int do_read(const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi) {
    FILE *fd = fopen(path, "r");
    if (fd==NULL)
        return -1;
    int res = fseek(fd, offset, 0);
    if (res!=0) {
        fclose(fd);
        return res;
    }
    return fread(buffer, size, 1, fd) < 0 ? -1 : 0;
}
