#include "qsocketrunnable.h"
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

QString url_pay = "/tickets/pay/";
QString url_sell = "/tickets/sell/";
QString url_tickets = "/tickets";
QString url_findTicket = "/tickets/";

QString error_msg_400 = "{\"error\":\"400\", \"message\":\"incorrect id\"}";
QString error_msg_404 = "{\"error\":\"404\", \"message\":\"ticket not found\"}";


QString getIDTicket(QString url);
bool checkFormatID(QString ticket_id);
void qweqew(QString url);

QSocketRunnable::QSocketRunnable(int handle) : descriptor(handle) { }

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
    QString header = lst[0];                    // header of HTTP request
    QRegExp header_split(" ");
    QStringList head = header.split(header_split);

    QStringList splittedHeader = head[1].split("/");

    if(head.first() == "GET" && head[1] == url_tickets) {
        // database -> array -> jformat -> json_array
        JsonFormatter jf;

        json_f = jf.getIdValues();

    }

    QRegExp httpFind("/tickets/\\d{8}");
    if(head.first() == "GET" && httpFind.exactMatch(head[1])) {

        qDebug("tickets/8cifr");
        QString ticket_id = getIDTicket(head[1]);
        JsonFormatter jf;

        json_f = jf.getStatusById(ticket_id);

        if(ticket_id == "400"){
            json_f = error_msg_400;
        }

    }
    QRegExp httpSell("/tickets/sell/\\d{8}");
    if(head.first() == "GET" && httpSell.exactMatch(head[1])) {
        qDebug("tickets/sell/8cifr");
        QString ticket_id = getIDTicket(head[1]);
        JsonFormatter jf;

        json_f = jf.updateTicketStatus(ticket_id);

    }
    QRegExp httpPay("/tickets/pay/\\d{8}");
    if(head.first() == "GET" && httpPay.exactMatch(head[1])) {
        qDebug("tickets/pay/8cifr");
        QString ticket_id = getIDTicket(head[1]);
        QString json_in = lst.last();

        JsonParser parser(json_in);

        auto json_tree = parser.tree();
        for(auto& item: json_tree){
            qDebug() << item;
        }

    }
    /* --------------------------------------------------------------------------------FOR GET REQUEST */
    QString http_resp_err = "HTTP/1.1 400 ERROR\r\n"
                       "Content-Type: application/json; charset=utf-8 \r\n\r\n"
                       + json_f;

    QString http_resp_ok = "HTTP/1.1 200 OK\r\n"
                       "Content-Type: application/json; charset=utf-8 \r\n\r\n"
                       + json_f;
    /* --------------------------------------------------------------------------------FOR GET REQUEST */


    socket->write(http_resp_ok.toUtf8());
    socket->waitForBytesWritten();

    socket->disconnectFromHost();
    socket->close();
    socket->deleteLater();
}

QString getIDTicket(QString url){

    QRegExp split_by_slash("/");
    QStringList splittedString = url.split(split_by_slash);
    qDebug() << splittedString.last();

    if(checkFormatID(splittedString.last()) && splittedString.last().size() == 8) {
        return splittedString.last();
    }

    return "400";
}

void qweqew(QString url){
    QRegExp split_by_slash("/");
    QStringList splittedString = url.split(split_by_slash);
    for(auto&i:splittedString){
        qDebug() << i;
    }
}

bool checkFormatID(QString ticket_id){
    for(auto&i: ticket_id){
        if(i.isLetter()){
            return false;
        }
    }
    return true;
}
