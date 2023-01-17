#ifndef JSONFORMATTER_H
#define JSONFORMATTER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtDebug>
#include <QString>

#include "database.h"

class JsonFormatter
{
public:
    JsonFormatter();
    QString getJsonString();
    QString getIdValues();
    QString getStatusById(QString ticket_id);
    QString updateTicketStatus(QString ticket_id);
private:
    database* m_db;
};

#endif // JSONFORMATTER_H
