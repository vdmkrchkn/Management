#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QMutex>
#include <QMutexLocker>

// поток-исполнитель
class Worker : public QThread
{
    Q_OBJECT
public:
    // создание
    Worker(int id);
    // прекращение работы
    void stop();    
protected:
    // запуск
    virtual void run();
private:
    // для обеспечения атомарности операций записи
    QMutex m_Mutex;
    // признак останова
    volatile bool m_vbStopped;
    // символ для печати
    int m_nId;
};

#endif // WORKER_H
