#include "QSocketRunnable.h"
#include <QString>
#include <memory>


QSocketRunnable::QSocketRunnable(int handle) : m_descriptor(handle) { }

void QSocketRunnable::run()
{
    QTcpSocket* socket = new QTcpSocket();
    socket->setSocketDescriptor(m_descriptor);
    socket->waitForReadyRead();
    QString request_data = QString(socket->readAll());

    HttpRequestHandler handler(request_data);
    handler.makeResponse();

    QString http_response_result = handler.getHttpResponse();
    socket->write(http_response_result.toUtf8());
    socket->waitForBytesWritten(90000);

    socket->disconnectFromHost();
    socket->close();
    socket->deleteLater();
}

