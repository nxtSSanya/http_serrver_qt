#ifndef SIGNALHANDLERS_H
#define SIGNALHANDLERS_H
#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <signal.h>
#include <unistd.h>

namespace SignalHandlers{
    sig_atomic_t sig_value = 0;

    void catchUnixSignals(const std::vector<int>& quitSignals) {

        auto handler = [](int sig) -> void {
            std::cout << "Quit the application (user request signal = " + std::to_string(sig) + ")\n";
            sig_value = sig;
        };

        for ( int sig : quitSignals )
            signal(sig, handler);

    }
}

#endif // SIGNALHANDLERS_H
