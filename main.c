//
// Created by dondish on 7/9/18.
//
#define FUSE_USE_VERSION 31
#include "fs.h"
#include <fuse3/fuse.h>
#include <unistd.h>
#include <utime.h>

static struct fuse_operations ops = {
    .mkdir = do_mkdir,
    .getattr = lstat,
    .mknod = do_mknod,
    .read = do_read,
    .write = do_write,
    .init = do_init,
    .access = access,
    .rmdir = rmdir,
    .open = open,
    .chmod = chmod,
    .chown = chown
};

int main(int argc, char *argv[]) {
    return fuse_main(argc, argv, &ops, NULL);
}