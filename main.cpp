#include <QCoreApplication>
#include "qthreadpoolserver.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qthreadpoolserver server;

    return a.exec();
}
