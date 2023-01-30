#include <QCoreApplication>
#include "QThreadPoolServer.h"
#include "Database.h"
#include "SignalHandlers.h"
#include "signal.h"
#include "ConfigReader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThreadPoolServer server;
    SignalHandlers::catchUnixSignals({SIGINT, SIGTERM});

    if(SignalHandlers::sig_value == SIGTERM)
        server.close();

    return a.exec();
}
