#include <QCoreApplication>
#include "qthreadpoolserver.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //database db("localhost", "db_lottery", "root", "Hellokisa228!");
    //db.processQuery("CREATE DATABASE IF NOT EXISTS lotery_db;USE lotery_db;CREATE TABLE IF NOT EXISTS TICKETS (ticket_id varchar(8) PRIMARY KEY,win_size int,ticket_status enum('Available', 'Sold', 'Paid'));");
    //db.getData();
    qthreadpoolserver server;

    return a.exec();
}
