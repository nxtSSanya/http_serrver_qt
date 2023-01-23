#ifndef QTHREADPOOLSERVER_H
#define QTHREADPOOLSERVER_H

#include <QTcpServer>
#include <QThreadPool>
#include <memory>

class QThreadPoolServer : public QTcpServer
{
public:
    explicit QThreadPoolServer();

    void incomingConnection(int handle) override;
private:
    std::shared_ptr<QThreadPool> m_threadPool;
};

#endif // QTHREADPOOLSERVER_H
