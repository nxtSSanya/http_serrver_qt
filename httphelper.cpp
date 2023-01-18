#include "httphelper.h"

QString http_code = "200 OK";
QString json_response = "";

QString http_find_url_tickets = "/tickets";
QRegExp http_find_ticket_regex("/tickets/\\d{8}");
QRegExp http_sell_ticket_regex("/tickets/sell/\\d{8}");
QRegExp http_pay_ticket_regex("/tickets/pay/\\d{8}");

httphelper::httphelper(QString request_data_in)
{
    m_request_data = request_data_in;
}

void httphelper::make_response(){
    JsonFormatter jf;

    QRegExp split_request_line_by_line("\r\n");
    QStringList lst = m_request_data.split(split_request_line_by_line);

    QString request_header = lst[0];

    QRegExp split_head_of_request_by_space(" ");
    QStringList head = request_header.split(split_head_of_request_by_space);

    QString http_request_type = head.first();
    QString http_page_request = head[1];

    if(http_request_type == "GET" && http_page_request == http_find_url_tickets) {
        json_response = jf.get_id_of_tickets();
        http_code = "200 OK";
    }
    else if(http_request_type == "GET" && http_find_ticket_regex.exactMatch(http_page_request)) {
        QString ticket_id = IDhelper::getIDTicket(http_page_request);

        json_response = jf.get_status_by_id(ticket_id);
        http_code = "200 OK";
    }
    else if(http_request_type == "GET" && http_sell_ticket_regex.exactMatch(http_page_request)) {
        QString ticket_id = IDhelper::getIDTicket(http_page_request);

        json_response = jf.sell_ticket(ticket_id);
        http_code = "200 OK";
    }
    else if(http_request_type == "GET" && http_pay_ticket_regex.exactMatch(http_page_request)) {
        QString ticket_id = IDhelper::getIDTicket(http_page_request);

        json_response = jf.pay_for_ticket(ticket_id);
        http_code = "200 OK";
    }
    else {
        QString ticket_id = IDhelper::getIDTicket(http_page_request);

        json_response = jf.process_error(ticket_id);
        http_code = "400 ERROR";
    }


    QString http_resp_ok = "HTTP/1.1 " + http_code + "\r\n"
                       "Content-Type: application/json; charset=utf-8 \r\n\r\n"
                       + json_response;

    m_http_response = http_resp_ok;

}

QString httphelper::get_http_response(){
    return m_http_response;
}

