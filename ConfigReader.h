#ifndef CONFIGREADER_H
#define CONFIGREADER_H
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QRegExp>
#include <QStringList>

#include <iostream>

class ConfigReader{
public:
    ConfigReader();
    QString getServerAddress();
    int getServerPort();
    int getServerTicketSize();
private:
    QString m_server_addr = "127.0.0.1";
    int m_server_port = 8080;
    int m_server_ticket_id_size = 8;
};



#endif // CONFIGREADER_H
