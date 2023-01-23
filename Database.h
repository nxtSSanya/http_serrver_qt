#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <vector>
#include <memory>
#include <iostream>

class Database
{
public:
    Database();
    Database(Database& other);
    bool processQuery(QString query);
    QString error();
    std::vector<QString> getIdOfTickets();
    std::pair<QString, QString> findTicketById(QString ticket_id);
    std::pair<QString, QString> sellTicket(QString ticket_id);
    std::pair<QString, QString> payForTicket(QString ticket_id);
    ~Database();
private:
    QSqlDatabase m_db;
    std::shared_ptr<QSqlQuery> m_query;
    QString m_error;
};

#endif // DATABASE_H
