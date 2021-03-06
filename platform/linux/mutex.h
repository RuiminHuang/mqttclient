/*
 * @Author: jiejie
 * @Github: https://github.com/jiejieTop
 * @Date: 2019-12-15 18:31:33
 * @LastEditTime : 2019-12-31 12:23:04
 * @Description: the code belongs to jiejie, please keep the author information and source code according to the license.
 */
#ifndef _MUTEX_H_
#define _MUTEX_H_
#include <pthread.h>

typedef struct platform_mutex {
    pthread_mutex_t mutex;
} platform_mutex_t;

int platform_mutex_init(platform_mutex_t* m);
int platform_mutex_lock(platform_mutex_t* m);
// int platform_mutex_trylock(platform_mutex_t* m);
int platform_mutex_unlock(platform_mutex_t* m);
int platform_mutex_destroy(platform_mutex_t* m);

#endif
