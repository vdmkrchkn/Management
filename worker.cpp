#include "worker.h"
#include <iostream>

Worker::Worker(int id) : QThread(0), m_vbStopped(false), m_nId(id){}

void Worker::stop()
{
    QMutexLocker lock(&m_Mutex);
    m_vbStopped = true;
}

void Worker::run()
{
    while(!m_vbStopped) {        
        std::cerr << m_nId << std::endl;
        QThread::sleep(2);
    }    
    QMutexLocker lock(&m_Mutex);
    m_vbStopped = false;
}
