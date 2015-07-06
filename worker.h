#ifndef WORKER_H
#define WORKER_H

#include <QThread>
// поток-исполнитель
class Worker : public QThread
{
    Q_OBJECT
public:
    // создание
    Worker(char chData);
    // прекращение работы
    void stop();
protected:
    // запуск
    virtual void run();
private:
    // признак останова
    volatile bool m_vbStopped;
    // символ для печати
    char m_chData;
};

#endif // WORKER_H
