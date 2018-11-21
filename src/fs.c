//
// Created by dondish on 11/14/18.
//

#include <stdlib.h>
#include <leveldb/c.h>
#include <memory.h>
#include "fs.h"
#include <string.h>

/**
 * Add a file to the cache
 * @param file file properties
 * @return error codes
 */
char *addFile(safst_file *file) {
    cJSON *json = fileToJson(file); // serialize to json
    char *err = NULL;

    leveldb_options_t *opts = leveldb_options_create();
    leveldb_options_set_create_if_missing(opts, 1); // create the file if it doesn't exist
    leveldb_t *db = leveldb_open(opts, "filescache", &err); // open the cache

    leveldb_free(db);
    leveldb_free(opts);
    if (err != NULL) {
        leveldb_free(err);
        cJSON_free(json);
        free(file->filename);
        free(file);
        return err;
    }
    leveldb_free(err);

    char *formatted = cJSON_Print(json);
    leveldb_writeoptions_t *writeoptions = leveldb_writeoptions_create();
    leveldb_put(db, writeoptions, file->filename, strlen(file->filename), formatted, strlen(formatted), &err);

    leveldb_free(writeoptions);
    leveldb_free(db);
    cJSON_free(json);
    free(file->filename);
    free(file);
    free(formatted);

    if (err != NULL) {
        return err;
    }

    leveldb_free(err);
    return NULL;

}

/**
 * Get file metadata
 * @param path the path
 * @return the file
 */
safst_file *getFile(char *path, char **err) {
}

/**
 * Delete the file metadata
 * @param path the path
 * @return the meta data of the file deleted
 */
safst_file *deleteFile(char *path, char **err) {
    safst_file *old = getFile(path, err);

    if (*err != NULL) {
        free(old);
        free(path);
        return NULL;
    }

    leveldb_options_t *opts = leveldb_options_create();
    leveldb_options_set_create_if_missing(opts, 1); // create the file if it doesn't exist
    leveldb_t *db = leveldb_open(opts, "filescache", err); // open the cache
    
    leveldb_free(opts);
    if (*err != NULL) {
        leveldb_free(db);
        return old;
    }
    leveldb_free(err);

    leveldb_writeoptions_t *wopts = leveldb_writeoptions_create();
    leveldb_delete(db, wopts, path, strlen(path), err);

    leveldb_free(db);
    leveldb_free(wopts);
    free(path);

    if (*err != NULL) {
        return old;
    }

    return old;
}

/**
 * Update the file metadata
 * @param path the path
 * @return the meta data of the old file
 */
safst_file *editFile(safst_file *path, char **err) {

}