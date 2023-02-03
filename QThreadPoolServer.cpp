#include "QThreadPoolServer.h"
#include "QSocketRunnable.h"
#include "ConfigReader.h"
#include <memory>

QThreadPoolServer::QThreadPoolServer()
{
    ConfigReader reader(config_file_path);
    if(!reader.error().isEmpty()) {
        std::cout << reader.error().toStdString() << "\n";
        std::cout << "Server starting by default in address: " << reader.getServerAddress().toStdString() << ":" << reader.getServerPort() << "\n";
        std::cout << "Ticket size is: " << reader.getServerTicketSize() << "\n";
    }
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
