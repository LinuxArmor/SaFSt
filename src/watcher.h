//
// Created by dondish on 11/7/18.
//

#ifndef SAFST_WATCHER_H
#define SAFST_WATCHER_H

#include <pthread.h>

int init();

void shutdown(pthread_t *pthread);

#endif //SAFST_WATCHER_H
