//
// Created by dondish on 7/10/18.
//

#define FUSE_USE_VERSION 31
#include "fuse_oper.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

DIR *root;

void *do_init(struct fuse_conn_info *conn, struct fuse_config *config) {
    config->use_ino = 1;
    config->entry_timeout = 0;
    config->attr_timeout = 0;
    config->negative_timeout = 0;
    root = open()
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

int do_getattr(const char *path, struct stat *stat, struct fuse_file_info *fi) {
    return lstat(path, stat);
}

int do_open(const char *path, struct fuse_file_info *fi) {
    return open(path, fi->flags);
}

int do_chmod(const char *path, mode_t mode, struct fuse_file_info *info) {
    return chmod(path, mode);
}

int do_chown(const char *path, uid_t uid, gid_t gid, struct fuse_file_info *info) {
    return chown(path, uid, gid);
}

int do_readdir(const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *info,enum fuse_readdir_flags fs) {
    DIR *dir = opendir(path);
    struct dirent *ent;
    if (dir == NULL) {
        return -1;
    }
    while ((ent = readdir(dir))!= NULL) {
        struct stat st;
        memset(&st, 0, sizeof(st));
        st.st_ino = ent->d_ino;
        st.st_mode = ent->d_type << 12;
        if (filler(buffer, path, &st, ent->d_off, 0))
            break;
    }
    closedir(dir);
    return 0;
}