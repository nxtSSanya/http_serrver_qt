#ifndef HTTPREQUESTHANDLER_H
#define HTTPREQUESTHANDLER_H
#include <QString>
#include <QStringList>
#include <QRegExp>

#include "IDHelper.h"
#include "JsonFormatter.h"
#include "Database.h"
#include "HttpParser.h"

class HttpRequestHandler
{
public:
    HttpRequestHandler(const QString& request_data_in);
    void makeResponse();
    QString getHttpResponse();
    ~HttpRequestHandler();
private:
    QString m_url_addr;
    QString m_ticket_id;
    QString m_request_type;

    Database* m_db;
    QString m_http_response;

    QString getStatusById(const QString& ticket_id);
    QString payForTicket(const QString& ticket_id);
    QString sellTicket(const QString& ticket_id);
    QString getIdOfTickets();
};

#endif // HTTPREQUESTHANDLER_H
