#include "ConfigReader.h"

ConfigReader::ConfigReader()
{
    QFile inputFile("server_config.txt");
    QRegExp regex(": ");
    inputFile.open(QIODevice::ReadOnly);
    std::vector<QString> values_from_file;

    QTextStream stream(&inputFile);

    for (QString line = stream.readLine(); !line.isNull(); line = stream.readLine()) {
        QStringList splitted = line.split(regex);
        values_from_file.push_back(splitted.last());
    };

    inputFile.close();

    m_server_addr = values_from_file[0];
    m_server_port = values_from_file[1].toInt();
    m_server_ticket_id_size = values_from_file[2].toInt();
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
