#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <pthread.h>

#include <string>

class MyThread 
{
public:
    explicit MyThread();
    ~MyThread();

    void start();

private:
    static void *m_thread_callback(void *arg);
    
    pthread_t m_thread;
    std::string m_str = "default";
};

#endif // MYTHREAD_H
