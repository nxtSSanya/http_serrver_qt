#ifndef QTHREADPOOLSERVER_H
#define QTHREADPOOLSERVER_H

#include <QTcpServer>
#include <QThreadPool>

class qthreadpoolserver : public QTcpServer
{
public:
    explicit qthreadpoolserver();

    void incomingConnection(int handle);
private:
    QThreadPool* m_threadPool;
};

#endif // QTHREADPOOLSERVER_H
