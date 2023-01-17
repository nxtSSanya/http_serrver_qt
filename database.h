#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <vector>

class database
{
public:
    database(QString hostname, QString db_name, QString username, QString password);
    bool processQuery(QString query);
    QString error();
    std::vector<QString> getIdArray();
    std::pair<QString, QString> findById(QString ticket_id);
    QString sellTicket(QString ticket_id);
    ~database();
private:
    QSqlDatabase m_db;
    QSqlQuery* m_query;
    QString m_error;
};

#endif // DATABASE_H
