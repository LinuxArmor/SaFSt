//
// Created by dondish on 7/10/18.
//
#include <fuse.h>
#ifndef SAFST_FS_H
#define SAFST_FS_H
static int do_getattr(const char *path, struct stat *st);
static int do_readdir(const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi);
#endif //SAFST_FS_H

