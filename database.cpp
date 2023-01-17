#include "database.h"
#include "QSqlError"

database::database(QString hostname, QString db_name, QString username, QString password)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE"); //no MariaDB in qt
    m_db.setDatabaseName("./qwe.db");
    if(m_db.open()){
        qDebug() << "Opened successfully";
    }
    else{
        qDebug() << "Error";
    }
}

/*
CREATE DATABASE IF NOT EXISTS lotery_db;

USE lotery_db;

CREATE TABLE IF NOT EXISTS TICKETS (
  ticket_id varchar(8) PRIMARY KEY,
  win_size int,
  ticket_status enum('Available', 'Sold', 'Paid')
);
*/

bool database::processQuery(QString query)
{
    m_query = new QSqlQuery(m_db);
    qDebug() << query;
    if(m_query->exec(query)){
        qDebug("ok");
        return true;
    }
    else {
        qDebug() << query;
        qDebug() << m_query->lastError().text();
        m_error = m_query->lastError().text();
        return false;
    }
}

QString database::error()
{
    return m_error;
}

std::vector<QString> database::getIdArray()
{
    std::vector<QString> id_values;
    processQuery("select ticket_id from TICKETS;");
    while(m_query->next()){
        id_values.push_back(m_query->value(0).toString());
        qDebug() << m_query->value(0).toString();
    }
    return id_values;
}

std::pair<QString, QString> database::findById(QString ticket_id)
{
    std::pair<QString, QString> ticket_status;
    processQuery("select ticket_id, ticket_status from TICKETS where ticket_id = \"" + ticket_id + "\";");
    while(m_query->next()){
        ticket_status.first = m_query->value(0).toString();
        ticket_status.second = m_query->value(1).toString();
    }
    return ticket_status;
}

QString database::sellTicket(QString ticket_id)
{
    QString result = "";
    std::pair<QString, QString> found_ticket = findById(ticket_id);
    if(found_ticket.first.isEmpty() && found_ticket.second.isEmpty()) {
        result = "Ticket not found";
    }
    else if(processQuery("update TICKETS set ticket_status = \"sold\" where ticket_id = \"" + ticket_id + "\";")) {
        result = "Success sold";
    }
    else {
        result = m_query->lastError().text();
    }
    return result;
}

database::~database()
{
    m_db.close();
}
