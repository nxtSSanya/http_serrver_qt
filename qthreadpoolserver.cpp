#include "qthreadpoolserver.h"
#include "qsocketrunnable.h"

qthreadpoolserver::qthreadpoolserver()
{
    listen(QHostAddress::LocalHost, 8080);
    m_threadPool = new QThreadPool(this);
    //m_threadPool->start()
}

void qthreadpoolserver::incomingConnection(int handle)
{
    QSocketRunnable* runnable = new QSocketRunnable(handle);
    m_threadPool->start(runnable);
}
