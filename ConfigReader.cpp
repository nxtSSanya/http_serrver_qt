#include "ConfigReader.h"

QString config_file_path;

ConfigReader::ConfigReader(const QString& file_name)
{
    const QString address_config_field_name = "server_ip_address";
    const QString port_config_field_name = "server_port";
    const QString ticket_size_config_field_name = "ticket_id_size";

    QFile input_file(file_name);
    QRegExp regex(": ");
    if(input_file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&input_file);

        for (QString line = stream.readLine(); !line.isNull(); line = stream.readLine()) {
            QStringList splitted = line.split(regex);

            if(splitted.first() == address_config_field_name) {
                m_server_addr = splitted.at(1);
            }
            if(splitted.first() == port_config_field_name) {
                m_server_port = splitted.at(1).toInt();
            }
            if(splitted.first() == ticket_size_config_field_name) {
                m_server_ticket_id_size = splitted.at(1).toInt();
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
