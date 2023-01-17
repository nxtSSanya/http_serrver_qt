#ifndef QSOCKETRUNNABLE_H
#define QSOCKETRUNNABLE_H

#include <QRunnable>
#include <QTcpSocket>
#include <QtDebug>
#include <QString>

#include "jsonparser.h"
#include "jsonformatter.h"

class QSocketRunnable : public QRunnable
{
public:
    QSocketRunnable(int handle);
    void run() override;
private:
    int descriptor;
};

#endif // QSOCKETRUNNABLE_H
