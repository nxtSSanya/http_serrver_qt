#ifndef QSOCKETRUNNABLE_H
#define QSOCKETRUNNABLE_H

#include <QRunnable>
#include <QTcpSocket>
#include <QtDebug>
#include <QString>

#include "IDHelper.h"
#include "JsonFormatter.h"
#include "HttpRequestHandler.h"

class QSocketRunnable : public QRunnable
{
public:
    QSocketRunnable(const int& handle);
    void run() override;
private:
    int m_descriptor;
};

#endif // QSOCKETRUNNABLE_H
