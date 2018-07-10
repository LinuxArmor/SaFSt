//
// Created by dondish on 7/10/18.
//

#include "db.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

static int create_db() {
    FILE *db;
    db = fopen("stats.db", "w+");
    if (db == NULL) {
        printf("Error creating database");
        return -1;
    }
    fclose(db);
}

int add_record(struct stat *record) {
    FILE *db = fopen("stats.db", "w+");
    if (db == NULL) {
        printf("Error opening database");
        return -1;
    }
    fseek(db, 0, SEEK_END);
    fwrite(record, sizeof(record), 1, db);
    fclose(db);
}
