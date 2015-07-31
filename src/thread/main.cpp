#include <unistd.h>

#include <iostream>

#include "mythread.h"

int main(int argc, char *argv[]) 
{
    MyThread *thread = new MyThread;
    thread->start();

    while (true)
        sleep(1);

    return 0;
}
