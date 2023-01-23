#include <QCoreApplication>
#include "QThreadPoolServer.h"
#include "Database.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QThreadPoolServer server;

    return a.exec();
}
