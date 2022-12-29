#include "qsocketrunnable.h"

QSocketRunnable::QSocketRunnable(int handle) : descriptor(handle)
{

}

void QSocketRunnable::run()
{
    QTcpSocket* socket = new QTcpSocket();
    socket->setSocketDescriptor(descriptor);


    socket->waitForReadyRead();
    qDebug() << socket->readLine();
    qDebug() << socket->readLine();
    qDebug() << socket->readLine();
    qDebug() << socket->readLine();
    qDebug() << socket->readLine();
    qDebug() << socket->readLine();
    qDebug() << socket->readLine();
    qDebug() << socket->readLine();
    qDebug() << socket->readLine();
    qDebug() << socket->readLine();
    qDebug() << socket->readLine();
    qDebug() << socket->readLine();
    qDebug() << socket->readLine();
    qDebug() << socket->readLine();
    qDebug() << socket->readLine();
    qDebug() << socket->readLine();
    qDebug() << socket->readLine();
    qDebug() << socket->readLine();
    qDebug() << socket->readLine();
    QString response = "HTTP/1.1 200 OK\r\n"
                       "Content-Type: application/json; charset=utf-8 \r\n\r\n"
                       "{\"type\":\"qweqwe\"}";
    socket->write(response.toUtf8());
    socket->waitForBytesWritten();

    socket->disconnectFromHost();
    socket->close();
    socket->deleteLater();
}
