#include <QCoreApplication>
#include "QThreadPoolServer.h"
#include "Database.h"
#include "SignalHandlers.h"
#include "signal.h"
#include "ConfigReader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SignalHandlers::catchUnixSignals({SIGINT, SIGTERM});
    std::cout << "Enter the path to the config file: ";
    std::string input_file_path;
    std::cin >> input_file_path;
    config_file_path = QString::fromStdString(input_file_path);

    QThreadPoolServer server;

    if(SignalHandlers::sig_value == SIGTERM) {
        server.close();
        return a.exec();
    }

    return a.exec();
}
