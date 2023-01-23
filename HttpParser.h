#ifndef HTTPPARSER_H
#define HTTPPARSER_H

#include <QString>
#include <QRegExp>
#include <QStringList>
#include "IDHelper.h"



class HttpParser
{
public:
    HttpParser(const QString& data_in);
    QString getTicketId();
    QString getHttpPageRequest();
    QString getHttpRequestType();
private:
    QString m_ticket_id;
    QString m_http_page_request;
    QString m_http_request_type;
};

#endif // HTTPPARSER_H
