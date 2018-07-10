//
// Created by dondish on 7/10/18.
//
#include <fuse.h>
#ifndef SAFST_FS_H
#define SAFST_FS_H
static int do_mknod(const char *path, mode_t mode, dev_t dev);
static int do_read(const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi);
#endif //SAFST_FS_H

