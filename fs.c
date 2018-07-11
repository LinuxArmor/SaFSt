//
// Created by dondish on 7/10/18.
//

#define FUSE_USE_VERSION 31
#include "fs.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

void *do_init(struct fuse_conn_info *conn, struct fuse_config *config) {
    config->use_ino = 1;
    config->entry_timeout = 0;
    config->attr_timeout = 0;
    config->negative_timeout = 0;
    return NULL;
}

int do_mknod(const char *path, mode_t mode, dev_t dev) {
    if (S_ISREG(mode)) {  // allow only regular files
        return mknod(path, mode, dev);
    }
    return -1;
}

int do_read(const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi) {
    FILE *fd = fopen(path, "r");
    (void) fi;
    if (fd==NULL)
        return -1;
    int res = fseek(fd, offset, 0);
    if (res!=0) {
        fclose(fd);
        return res;
    }
    res = fread(buffer, size, 1, fd) < 0 ? -1 : 0;
    fclose(fd);
    return res;
}

int do_write(const char *path, const char *data, size_t size, off_t offset, struct fuse_file_info *fi) {
    FILE *fd = fopen(path, "w");
    (void) fi;
    if (fd==NULL)
        return -1;
    int res = fseek(fd, offset, 0);
    if (res!=0) {
        fclose(fd);
        return res;
    }
    res = fwrite(data, size, 1, fd) < 0 ? -1 : 0;
    // Add check for permission change
    fclose(fd);
    return res;
}

int do_mkdir(const char *path, mode_t mode) {
    return mkdir(path, mode);
}