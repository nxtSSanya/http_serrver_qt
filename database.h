#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>

class database
{
public:
    database(QString hostname, QString db_name, QString username, QString password);
    void processQuery(QString query);
    void getData();
private:
    QSqlDatabase m_db;
    QSqlQuery* m_query;
};

#endif // DATABASE_H
