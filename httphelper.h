#ifndef HTTPHELPER_H
#define HTTPHELPER_H
#include <QString>
#include <QStringList>
#include <QRegExp>

#include "idhelper.h"
#include "jsonformatter.h"
#include "database.h"

class httphelper
{
public:
    httphelper(QString request_data_in);
    void make_response();
    QString get_http_response();
private:
    QString m_request_data;
    QString m_http_response;
};

#endif // HTTPHELPER_H
