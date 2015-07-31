#include "mythread.h"

#include <iostream>

MyThread::MyThread() 
{
}

MyThread::~MyThread() 
{
}

void MyThread::start() 
{
    pthread_create(&m_thread, NULL, m_thread_callback, this);
}

void *MyThread::m_thread_callback(void *arg) 
{
    MyThread *thisPtr = (MyThread *)arg;

    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << thisPtr->m_str << std::endl;

    return NULL;
}
