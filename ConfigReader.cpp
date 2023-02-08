#include "ConfigReader.h"

QString config_file_path;

ConfigReader::ConfigReader(const QString& file_name)
{
    const QString address_config_field_name = "server_ip_address";
    const QString port_config_field_name = "server_port";
    const QString ticket_size_config_field_name = "ticket_id_size";
    const QString database_name = "db_name";
    const QString db_host_name = "db_hostname";
    const QString db_username = "db_username";
    const QString db_password = "db_password";

    QFile input_file(file_name);
    QRegExp regex(": ");
    if(input_file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&input_file);

        for (QString line = stream.readLine(); !line.isNull(); line = stream.readLine()) {
            QStringList splitted = line.split(regex);

            if(splitted.first() == address_config_field_name) {
                if(splitted.at(1).isEmpty()) {
                    m_error = "Some fields are empty\n";
                }
                else {
                    m_server_addr = splitted.at(1);
                }
            }
            if(splitted.first() == port_config_field_name) {
                if(splitted.at(1).isEmpty()) {
                    m_error = "Some fields are empty\n";
                }
                else {
                    m_server_port = splitted.at(1).toInt();
                }
            }
            if(splitted.first() == ticket_size_config_field_name) {
                if(splitted.at(1).isEmpty()) {
                    m_error = "Some fields are empty\n";
                }
                else {
                    m_server_ticket_id_size = splitted.at(1).toInt();
                }
            }
            if(splitted.first() == database_name) {
                if(splitted.at(1).isEmpty()) {
                    m_error = "Some fields are empty\n";
                }
                else {
                    m_database_name = splitted.at(1);
                }
            }
            if(splitted.first() == db_host_name) {
                if(splitted.at(1).isEmpty()) {
                    m_error = "Some fields are empty\n";
                }
                else {
                    m_db_host_name = splitted.at(1);
                }
            }
            if(splitted.first() == db_username) {
                if(splitted.at(1).isEmpty()) {
                    m_error = "Some fields are empty\n";
                }
                else {
                    m_db_username = splitted.at(1);
                }
            }
            if(splitted.first() == db_username) {
                if(splitted.at(1).isEmpty()) {
                    m_error = "Some fields are empty\n";
                }
                else {
                    m_db_username = splitted.at(1);
                }
            }
        };

        input_file.close();

        std::cout << "Addr: " << m_server_addr.toStdString() << "\nPort: " << m_server_port << "\nTicket size: " << m_server_ticket_id_size << "\n";
    }
    else {
        std::cout << "Cannot open the file, check your path and try again.\n";
    }
}

QString ConfigReader::getServerAddress()
{
    return m_server_addr;
}

int ConfigReader::getServerPort()
{
    return m_server_port;
}

int ConfigReader::getServerTicketSize()
{
    return m_server_ticket_id_size;
}

QString ConfigReader::getDbName()
{
    return m_database_name;
}

QString ConfigReader::getHostName()
{
    return m_db_host_name;
}

QString ConfigReader::getPassword()
{
    return m_db_password;
}

QString ConfigReader::getUsername()
{
    return m_db_username;
}

QString ConfigReader::error()
{
    return m_error;
}
