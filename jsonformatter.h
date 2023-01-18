#ifndef JSONFORMATTER_H
#define JSONFORMATTER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtDebug>
#include <QString>
#include <memory>

#include "database.h"
#include "idhelper.h"

class JsonFormatter
{
public:
    JsonFormatter();
    JsonFormatter(JsonFormatter& other);
    QString get_id_of_tickets();
    QString get_status_by_id(QString ticket_id);
    QString sell_ticket(QString ticket_id);
    QString pay_for_ticket(QString ticket_id);
    QString process_error(QString ticket_id);
    ~JsonFormatter();
private:
    database* m_db;
};

#endif // JSONFORMATTER_H
