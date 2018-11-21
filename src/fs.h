//
// Created by dondish on 11/14/18.
//

#ifndef SAFST_FS_H
#define SAFST_FS_H

#include <sys/types.h>
#include <cjson/cJSON.h>

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

cJSON *fileToJson(safst_file *file) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "mode", file->mode);
    cJSON_AddNumberToObject(json, "uid", file->uid);
    cJSON_AddNumberToObject(json, "gid", file->gid);
    cJSON_AddNumberToObject(json, "size", file->size);
    cJSON_AddNumberToObject(json, "ctime", file->ctime);
    cJSON_AddNumberToObject(json, "atime", file->atime);
    cJSON_AddNumberToObject(json, "mtime", file->mtime);
    cJSON_AddStringToObject(json, "filename", file->filename);
    return json;
}

/**
 * Add a file to the cache
 * @param file file properties
 * @return error codes
 */
char *addFile(safst_file *file);

/**
 * Get file metadata
 * @param path the path
 * @return the file
 */
safst_file *getFile(char *path, char **err);

/**
 * Delete the file metadata
 * @param path the path
 * @return the meta data of the file deleted
 */
safst_file *deleteFile(char *path, char **err);

/**
 * Update the file metadata
 * @param file the file
 * @return the meta data of the old file
 */
safst_file *editFile(safst_file *file, char **err);

#endif //SAFST_FS_H
