#include "QThreadPoolServer.h"
#include "QSocketRunnable.h"
#include "ConfigReader.h"
#include <memory>

QThreadPoolServer::QThreadPoolServer()
{
    ConfigReader reader(config_file_path);
    QHostAddress server_IP(reader.getServerAddress());
    int port = reader.getServerPort();

    listen(server_IP, port);
    m_threadPool = std::make_shared<QThreadPool>(this);
}

void QThreadPoolServer::incomingConnection(int handle)
{
    std::shared_ptr<QSocketRunnable> runnable = std::make_shared<QSocketRunnable>(handle);
    runnable->setAutoDelete(false);
    m_threadPool->start(runnable.get());
}

QThreadPoolServer::~QThreadPoolServer()
{
    m_threadPool->~QThreadPool();
}
