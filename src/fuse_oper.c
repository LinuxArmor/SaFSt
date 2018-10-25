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


/**
 * Concats the path to the given subpath
 * @param path the subpath
 * @return the full path to the directory
 */
char *make_path(const char *path) {
    char *dest = calloc(PATH_MAX, sizeof(char));
    strcpy(dest, "/usr/local/var/safst");
    strncat(dest, path, PATH_MAX);
    puts(dest);
    return dest;
}

void *do_init(struct fuse_conn_info *conn, struct fuse_config *config) {
    config->use_ino = 1;
    config->entry_timeout = 0;
    config->attr_timeout = 0;
    config->negative_timeout = 0;
    return NULL;
}

int do_mknod(const char *path, mode_t mode, dev_t dev) {
    const char *p = make_path(path);
    int res = mknod(p, mode, dev);
    free((void *) p);
    if (S_ISREG(mode)) {  // allow only regular files
        return res;
    }
    return -1;
}

int do_read(const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi) {
    const char *p = make_path(path);
    FILE *fd = fopen(p, "r");
    free((void *) p);
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
    const char *p = make_path(path);
    FILE *fd = fopen(p, "w");
    free((void *) p);
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
    const char *p = make_path(path);
    int re = mkdir(p, mode);
    free((void *) p);
    return re;
}

int do_getattr(const char *path, struct stat *stat, struct fuse_file_info *fi) {
    const char *p = make_path(path);
    int re = lstat(p, stat);
    free((void *) p);
    stat->st_mode |= S_IRUSR | S_IWUSR;
    return re;
}

int do_open(const char *path, struct fuse_file_info *fi) {
    const char *p = make_path(path);
    int re = open(make_path(path), fi->flags);
    free((void *) p);
    return re;
}

int do_chmod(const char *path, mode_t mode, struct fuse_file_info *info) {
    const char *p = make_path(path);
    int re = chmod(p, mode);
    free((void *) p);
    return re;
}

int do_chown(const char *path, uid_t uid, gid_t gid, struct fuse_file_info *info) {
    return AT_EACCESS;
}

int do_readdir(const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *info,enum fuse_readdir_flags fs) {
    const char *p = make_path(path);
    DIR *dir = opendir(make_path(path));
    struct dirent *ent;
    puts(make_path(path));
    if (dir == NULL) {
        return -1;
    }
    while ((ent = readdir(dir))!= NULL) {
        struct stat st;
        memset(&st, 0, sizeof(st));
        st.st_ino = ent->d_ino;
        st.st_mode = (__mode_t) (ent->d_type << 12 | S_IRUSR | S_IWUSR);
        if (filler(buffer, make_path(path), &st, ent->d_off, 0))
            break;
    }
    free((void *) p);
    closedir(dir);
    return 0;
}