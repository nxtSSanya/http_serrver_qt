#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <vector>

class database
{
public:
    database();
    database(database& other);
    bool processQuery(QString query);
    QString error();
    std::vector<QString> get_id_of_tickets();
    std::pair<QString, QString> find_ticket_by_id(QString ticket_id);
    QString sell_ticket(QString ticket_id);
    std::pair<QString, QString> pay_for_ticket(QString ticket_id);
    ~database();
private:
    QSqlDatabase m_db;
    QSqlQuery* m_query;
    QString m_error;
};

#endif // DATABASE_H
