#ifndef JSONFORMATTER_H
#define JSONFORMATTER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtDebug>
#include <QString>
#include <memory>

#include "Database.h"
#include "IDHelper.h"

class JsonFormatter
{
public:
    JsonFormatter();
    QString JsonGetIdOfTickets(std::vector<QString> tickets_list);
    QString JsonGetStatusById(std::pair<QString, QString> ticket_status);
    QString JsonSellTicket(std::pair<QString, QString> ticket_status);
    QString JsonPayForTicket(std::pair<QString, QString> ticket_status);
    QString JsonProcessError(QString ticket_id);
};

#endif // JSONFORMATTER_H
