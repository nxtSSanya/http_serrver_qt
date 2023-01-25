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
    QString JsonGetIdOfTickets(const std::vector<QString>& tickets_list);
    QString JsonGetStatusById(const std::pair<QString, QString>& ticket_status);
    QString JsonSellTicket(const std::pair<QString, QString>& ticket_status);
    QString JsonPayForTicket(const std::pair<QString, QString>& ticket_status);
    QString JsonProcessError(const QString& ticket_id);
};

#endif // JSONFORMATTER_H
