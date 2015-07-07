#include "worker.h"
#include <iostream>

Worker::Worker(char chData) : QThread(0), m_vbStopped(false), m_chData(chData){}

void Worker::stop()
{
    m_vbStopped = true;
}

void Worker::run()
{
    while(!m_vbStopped) {
        std::cout << m_chData << std::endl;
        QThread::sleep(2);
    }
    m_vbStopped = false;    
}
