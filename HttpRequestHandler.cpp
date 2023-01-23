#include "HttpRequestHandler.h"

QString http_find_url_tickets = "/tickets";
QRegExp http_find_ticket_regex("/tickets/\\d{8}");
QRegExp http_sell_ticket_regex("/tickets/sell/\\d{8}");
QRegExp http_pay_ticket_regex("/tickets/pay/\\d{8}");

HttpRequestHandler::HttpRequestHandler(QString request_data_in)
{
    HttpParser hParser(request_data_in);
    db = new Database();

    m_ticket_id = hParser.getTicketId();
    m_url_addr = hParser.getHttpPageRequest();
    m_request_type = hParser.getHttpRequestType();
}

void HttpRequestHandler::makeResponse(){

    QString http_code = "200 OK";
    QString json_response = "";

    JsonFormatter jf;

    if(m_request_type == "GET" && m_url_addr == http_find_url_tickets) {
        json_response = getIdOfTickets();
    }
    else if(m_request_type == "GET" && http_find_ticket_regex.exactMatch(m_url_addr)) {
        json_response = getStatusById(m_ticket_id);
    }
    else if(m_request_type == "GET" && http_sell_ticket_regex.exactMatch(m_url_addr)) {
        json_response = sellTicket(m_ticket_id);
    }
    else if(m_request_type == "GET" && http_pay_ticket_regex.exactMatch(m_url_addr)) {
        json_response = payForTicket(m_ticket_id);
    }
    else {
        json_response = jf.JsonProcessError(m_ticket_id);
        http_code = "400 ERROR";
    }


    QString http_resp_ok = "HTTP/1.1 " + http_code + "\r\n"
                       "Content-Type: application/json; charset=utf-8 \r\n\r\n"
                       + json_response;

    m_http_response = http_resp_ok;

}

QString HttpRequestHandler::getIdOfTickets(){
    JsonFormatter jff;
    auto json_formatted = jff.JsonGetIdOfTickets(db->getIdOfTickets());

    return json_formatted;
}

QString HttpRequestHandler::getStatusById(QString ticket_id){
    JsonFormatter jff;
    auto json_formatted = jff.JsonGetStatusById(db->findTicketById(ticket_id));

    return json_formatted;
}

QString HttpRequestHandler::payForTicket(QString ticket_id){
    JsonFormatter jff;
    auto json_formatted = jff.JsonPayForTicket(db->payForTicket(ticket_id));

    return json_formatted;
}

QString HttpRequestHandler::sellTicket(QString ticket_id){
    JsonFormatter jff;
    auto json_formatted = jff.JsonSellTicket(db->sellTicket(ticket_id));

    return json_formatted;
}

QString HttpRequestHandler::getHttpResponse(){
    return m_http_response;
}

HttpRequestHandler::~HttpRequestHandler()
{
    db->~Database();
}

