// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <iostream>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define STACK_SIZE 512
#define THREAD_NUM 1024

static pthread_mutex_t m_mutex = PTHREAD_MUTEX_INITIALIZER;

static void* m_thread_callback(void* arg) 
{
    pthread_mutex_lock(&m_mutex);
    std::cout << "DEBUG: " << __PRETTY_FUNCTION__ << time(NULL) << std::endl;
    sleep(3); // TODO: simulate heavy operation
    pthread_mutex_unlock(&m_mutex);
    return NULL;
}

int main(int argc, char* argv[]) 
{
    pthread_attr_t attr;
    pthread_t thread[THREAD_NUM];
    int i;
    
    if (pthread_attr_init(&attr) != 0) {
        std::cout << "ERROR: fail to init pthread_attr_t " << 
            strerror(errno) << std::endl;
        return -1;
    }
    if (pthread_attr_setstacksize(&attr, STACK_SIZE) != 0) {
        std::cout << "ERROR: fail to set stacksize " << strerror(errno) << std::endl;
    }

    for (i = 0; i < THREAD_NUM; i++) {
        pthread_create(&thread[i], &attr, &m_thread_callback, NULL);
    }

    while (true) ;

    if (pthread_attr_destroy(&attr) != 0) {
        std::cout << "ERROR: fail to destroy pthread_attr_t " << 
            strerror(errno) << std::endl;
    }

    return 0;
}
