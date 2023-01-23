#include "HttpParser.h"



HttpParser::HttpParser(const QString& data_in)
{
    QRegExp split_request_line_by_line("\r\n");
    QStringList lst = data_in.split(split_request_line_by_line);

    QString request_header = lst[0];

    QRegExp split_header_of_request_by_space(" ");
    QStringList head = request_header.split(split_header_of_request_by_space);

    m_http_request_type = head.first();
    m_http_page_request = head[1];
    m_ticket_id = IDhelper::getIDTicket(head[1]);

}

QString HttpParser::getTicketId()
{
    return m_ticket_id;
}

QString HttpParser::getHttpPageRequest()
{
    return m_http_page_request;
}

QString HttpParser::getHttpRequestType()
{
    return m_http_request_type;
}
