#include "database.h"
#include "QSqlError"

database::database()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE"); // errors with MariaDB and qt
    m_db.setDatabaseName("./qwe.db");
    if(m_db.open()){
        qDebug() << "Opened successfully";
    }
    else{
        qDebug() << "Error while opening";
    }
}

database::database(database &other)
{
    m_db = other.m_db;
    m_query = other.m_query;
    m_error = other.m_error;
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

std::vector<QString> database::get_id_of_tickets()
{
    std::vector<QString> id_values;
    processQuery("select ticket_id from TICKETS;");
    while(m_query->next()){
        id_values.push_back(m_query->value(0).toString());
        qDebug() << m_query->value(0).toString();
    }
    return id_values;
}

std::pair<QString, QString> database::find_ticket_by_id(QString ticket_id)
{
    std::pair<QString, QString> ticketID_status;
    processQuery("select ticket_id, ticket_status from TICKETS where ticket_id = \"" + ticket_id + "\";");
    while(m_query->next()){
        ticketID_status.first = m_query->value(0).toString();
        ticketID_status.second = m_query->value(1).toString();
    }
    return ticketID_status;
}

QString database::sell_ticket(QString ticket_id)
{
    QString result = "";
    if(processQuery("update TICKETS set ticket_status = \"sold\" where ticket_id = \"" + ticket_id + "\";")) {
        result = "success sold";
    }
    else {
        result = m_query->lastError().text();
    }
    return result;
}

std::pair<QString, QString> database::pay_for_ticket(QString ticket_id)
{
    std::pair<QString, QString> result_status_winsize = {"", ""};

    if(processQuery("update TICKETS set ticket_status = \"paid\" where ticket_id = \"" + ticket_id + "\";") &&
       processQuery("select win_size from TICKETS where ticket_id = \"" + ticket_id + "\";")) {

        m_query->first();
        result_status_winsize.first = "success paid";
        result_status_winsize.second = m_query->value(0).toString();
    }
    else {
        result_status_winsize.first = m_query->lastError().text();
        result_status_winsize.second = "";
    }

    return result_status_winsize;

}
database::~database()
{
    m_db.close();
}
