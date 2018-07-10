//
// Created by dondish on 7/9/18.
//
#include "fs.h"
#include <fuse.h>

static struct fuse_operations ops = {
    .mkdir = mkdir,
    .getattr = lstat,
    .mknod = do_mknod,
    .read = do_read
};

int main(int argc, char *argv[]) {
    return fuse_main(argc, argv, &ops, NULL);
}