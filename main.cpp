#include <QCoreApplication>
#include "qthreadpoolserver.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //database db("localhost", "db_lottery", "root", "Hellokisa228!");
    //db.processQuery("CREATE TABLE TICKETS(ticket_id TEXT PRIMARY KEY, win_size INT, ticket_status TEXT);");
    //db.getData();
    qthreadpoolserver server;

    return a.exec();
}
