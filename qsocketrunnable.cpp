#include "qsocketrunnable.h"
#include <QString>

QString getIDTicket(QString url);

QSocketRunnable::QSocketRunnable(int handle) : descriptor(handle)
{

}

void QSocketRunnable::run()
{
    QTcpSocket* socket = new QTcpSocket();
    socket->setSocketDescriptor(descriptor);
    socket->waitForReadyRead();

    // POST /index.html HTTP/1.1\r\n //

    QString json_f = "";

    QString data = QString(socket->readAll());
    qDebug() << data;
    QRegExp tagExp("\r\n");
    QStringList lst = data.split(tagExp);
    QString header = lst[0]; // header of HTTP request
    QRegExp header_split(" ");
    QStringList head = header.split(header_split);

    qDebug() << head.first(); // type of request
    qDebug() << head[1]; // domain

    if(head.first() == "GET" && head[1] == "/tickets"){
        qDebug() << "LIST WITH ALL TICKETS FROM DATABASE";
    }
    else if(head.first() == "GET" && head[1].contains("/tickets/")){
        qDebug() << "INDEX OF TICKET IS: ";
        QString ticket_id = getIDTicket(head[1]);
        QString status = "available";
        json_f = "{\"ticket_id\":\"" + ticket_id + "\"}";

    }
    else if(head.first() == "POST"){
        qDebug() << "POST REQUEST FOUND.";
    }


    QString response = "HTTP/1.1 200 OK\r\n"
                       "Content-Type: application/json; charset=utf-8 \r\n\r\n"
                       "{\"type\":\"qweqwe\"}";

    QString response_json = "HTTP/1.1 200 OK\r\n"
                       "Content-Type: application/json; charset=utf-8 \r\n\r\n"
                       +json_f;

    //socket->write(response.toUtf8());
    //socket->waitForBytesWritten();
    socket->write(response_json.toUtf8());
    socket->waitForBytesWritten();

    socket->disconnectFromHost();
    socket->close();
    socket->deleteLater();
}

QString getIDTicket(QString url){
    QRegExp split_by_slash("/");
    QStringList splittedString = url.split(split_by_slash);
    if(splittedString.size() - 1 > 2){
        qDebug() << "404";
    } else {
        qDebug() << splittedString.last();
    }
    return splittedString.last();
}
