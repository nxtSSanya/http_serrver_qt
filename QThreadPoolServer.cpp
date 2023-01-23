#include "QThreadPoolServer.h"
#include "QSocketRunnable.h"
#include "Config.h"
#include <memory>


QHostAddress server_IP(ServerConfig::server_ip_address);

QThreadPoolServer::QThreadPoolServer()
{
    listen(server_IP, ServerConfig::server_port);
    m_threadPool = std::make_shared<QThreadPool>(this);
}

void QThreadPoolServer::incomingConnection(int handle)
{
    std::shared_ptr<QSocketRunnable> runnable = std::make_shared<QSocketRunnable>(handle);
    m_threadPool->start(runnable.get());
}
