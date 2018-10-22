//
// Created by dondish on 7/9/18.
//
#define FUSE_USE_VERSION 31
#include "fuse_oper.h"
#include <fuse3/fuse.h>
#include <unistd.h>
#include <utime.h>
#include <stdio.h>

static struct fuse_operations ops = {
    .mkdir = do_mkdir,
    .getattr = do_getattr,
    .mknod = do_mknod,
    .read = do_read,
    .write = do_write,
    .init = do_init,
    .access = access,
    .rmdir = rmdir,
    .open = do_open,
    .chmod = do_chmod,
    .chown = do_chown,
    .readdir = do_readdir
};

int main(int argc, char *argv[]) {
    return before_init(argc, argv, &ops);
}