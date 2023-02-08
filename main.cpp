#include <QCoreApplication>
#include "QThreadPoolServer.h"
#include "Database.h"
#include "SignalHandlers.h"
#include "signal.h"
#include "ConfigReader.h"
#include <sstream>

std::string default_config_fileName = "config.yaml";

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(argc <= 1) {
        if (argv[0]) {
            std::cout << "Usage: " << argv[0] << " [file name]" << '\n';
        }
        else {
            std::cout << "Usage: [program name] [file name]" << '\n';
        }
        return 1;
    }

    std::stringstream convert_arg_to_string{argv[1]};
    std::string input_file_path;
    SignalHandlers::catchUnixSignals({SIGINT, SIGTERM});
    if (!(convert_arg_to_string >> input_file_path)) {
        input_file_path = default_config_fileName;
    }

    config_file_path = QString::fromStdString(input_file_path);

    QThreadPoolServer server;

    if(SignalHandlers::sig_value == SIGTERM) {
        server.close();
        return a.exec();
    }

    return a.exec();
}
