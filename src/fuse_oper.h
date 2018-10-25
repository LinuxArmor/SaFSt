//
// Created by dondish on 7/10/18.
//
#include <fuse3/fuse.h>
#include <sys/types.h>
#include <dirent.h>

#ifndef SAFST_FS_H
#define SAFST_FS_H

int do_mknod(const char *path, mode_t mode, dev_t dev);
int do_read(const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi);
int do_write(const char *path, const char *data, size_t size, off_t offset, struct fuse_file_info *fi);
void *do_init(struct fuse_conn_info *conn, struct fuse_config *config);
int do_mkdir(const char *path, mode_t mode);
int do_getattr(const char *path, struct stat *stat, struct fuse_file_info *fi);
int do_open(const char *path, struct fuse_file_info *fi);
int do_chmod(const char *path, mode_t mode, struct fuse_file_info *info);
int do_chown(const char *path, uid_t uid, gid_t gid, struct fuse_file_info *info);
int do_readdir(const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *info,enum fuse_readdir_flags fs);
#endif //SAFST_FS_H

