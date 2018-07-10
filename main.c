//
// Created by dondish on 7/9/18.
//
#include "fs.h"
#include "db.h"
#include <fuse.h>

static struct fuse_operations ops = {
    .getattr = do_getattr,
    .readdir = do_readdir,
            .read = do_read
};

int main(int argc, char *argv[]) {
    if (create_db()!=0) return -1;
    return fuse_main(argc, argv, &ops, NULL);
}