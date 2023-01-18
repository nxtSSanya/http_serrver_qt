#include "qsocketrunnable.h"
#include <QString>


QSocketRunnable::QSocketRunnable(int handle) : descriptor(handle) { }

void QSocketRunnable::run()
{
    QTcpSocket* socket = new QTcpSocket();
    socket->setSocketDescriptor(descriptor);
    socket->waitForReadyRead();
    QString request_data = QString(socket->readAll());

    httphelper http_parser(request_data);
    http_parser.make_response();

    QString http_response_result = http_parser.get_http_response();

    socket->write(http_response_result.toUtf8());
    socket->waitForBytesWritten();

    socket->disconnectFromHost();
    socket->close();
    socket->deleteLater();
}

