#ifndef CONFIGREADER_H
#define CONFIGREADER_H
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QRegExp>
#include <QStringList>
#include <unordered_map>

#include <iostream>

extern QString config_file_path;

class ConfigReader{
public:
    ConfigReader(const QString& file_name);
    QString getServerAddress();
    int getServerPort();
    int getServerTicketSize();
    QString getDbName();
    QString getHostName();
    QString getUsername();
    QString getPassword();
    QString error();
private:
    QString m_server_addr = "127.0.0.1";
    int m_server_port = 8080;
    int m_server_ticket_id_size = 8;
    QString m_database_name = "";
    QString m_db_host_name = "";
    QString m_db_username = "";
    QString m_db_password = "";

    QString m_error = "";
};



#endif // CONFIGREADER_H
