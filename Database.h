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
    Database(QString hostname, QString db_name, QString username, QString password);
    Database(Database& other);

    QString error();
    bool getDoneInfo();
    std::vector<QString> getIdOfTickets();
    std::pair<QString, QString> findTicketById(const QString& ticket_id);
    std::pair<QString, QString> sellTicket(const QString& ticket_id);
    std::pair<QString, QString> payForTicket(const QString& ticket_id);
    ~Database();
private:
    bool processQuery(const QString& query);
    QSqlDatabase m_db;
    std::shared_ptr<QSqlQuery> m_query;
    QString m_error;
    bool m_isQueryDone;
};

#endif // DATABASE_H
