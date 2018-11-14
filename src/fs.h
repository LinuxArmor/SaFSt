//
// Created by dondish on 11/14/18.
//

#ifndef SAFST_FS_H
#define SAFST_FS_H

#include <sys/types.h>

typedef struct {
    mode_t mode; // mode
    uid_t uid; // uid of owner
    gid_t gid; // gid of group
    long int size; // the size of the file
    long int ctime; // creation time in ms
    long int atime; // the last time the file was accessed in ms
    long int mtime; // the last time the file was modified in ms
    char *filename; // the filename / path
} safst_file;

typedef struct {

} safst_dir;

#endif //SAFST_FS_H
