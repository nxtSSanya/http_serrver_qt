#include "database.h"

database::database(QString hostname, QString db_name, QString username, QString password)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE"); //no MariaDB in qt
    m_db.setDatabaseName("./qwe.db");
    m_db.open();
    m_query = new QSqlQuery(m_db);
    //m_db.setHostName(hostname);
    //m_db.setDatabaseName(db_name);
    //m_db.setUserName(username);
    //m_db.setPassword(password);
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

void database::processQuery(QString query)
{
    m_query->exec(query);
}

void database::getData()
{
   processQuery("INSERT INTO TICKETS VALUES(\"00000001\", 123123);");
   processQuery("select * from TICKETS");
   while(m_query->next()){
       qDebug() << m_query->result();
   }
}
