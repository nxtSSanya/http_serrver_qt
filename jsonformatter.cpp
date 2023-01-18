#include "jsonformatter.h"

JsonFormatter::JsonFormatter()
{
    m_db = new database();
}

JsonFormatter::JsonFormatter(JsonFormatter &other)
{
    m_db = other.m_db;
}

QString JsonFormatter::get_id_of_tickets()
{
    std::vector<QString> id_vec = m_db->get_id_of_tickets();
    QJsonObject jsonItem;
    QJsonArray jsonIdArray;

    for(auto&i:id_vec){
        jsonItem["ticket_id"] = i;
        jsonIdArray.append(jsonItem);
    }

    QJsonDocument jsonId_doc(jsonIdArray);
    QString jsonId_string = jsonId_doc.toJson();

    return jsonId_string;
}

QString JsonFormatter::get_status_by_id(QString ticket_id)
{
    std::pair<QString, QString> ticket_status = m_db->find_ticket_by_id(ticket_id);
    QJsonObject jsonItem;

    if(ticket_status.first.isEmpty() && ticket_status.second.isEmpty()) {
        jsonItem["code"] = "404";
        jsonItem["message"] = "ticket not found";
    }
    else {
        jsonItem["ticket_id"] = ticket_status.first;
        jsonItem["ticket_status"] = ticket_status.second;
    }

    QJsonDocument jsonTicketInfo_doc(jsonItem);
    QString jsonTicketInfo_string = jsonTicketInfo_doc.toJson();

    return jsonTicketInfo_string;
}

QString JsonFormatter::sell_ticket(QString ticket_id)
{
    std::pair<QString, QString> ticket_status = m_db->find_ticket_by_id(ticket_id);
    QJsonObject jsonItem;

    if(ticket_status.second == "paid" || ticket_status.second == "sold"){
        jsonItem["code"] = "400";
        jsonItem["message"] = "ticket has already been sold or paid";
    }
    else if(ticket_status.first.isEmpty() && ticket_status.second.isEmpty()) {
        jsonItem["code"] = "404";
        jsonItem["message"] = "ticket not found";
    }
    else {
        jsonItem["ticket_id"] = ticket_id;
        jsonItem["status"] = m_db->sell_ticket(ticket_id);
    }

    QJsonDocument jsonSellStatus_doc(jsonItem);
    QString jsonSellStatus_string = jsonSellStatus_doc.toJson();

    return jsonSellStatus_string;
}

QString JsonFormatter::pay_for_ticket(QString ticket_id)
{
    std::pair<QString, QString> ticket_status = m_db->find_ticket_by_id(ticket_id);
    QJsonObject jsonItem;
    if(ticket_status.second == "paid" || ticket_status.second == "available"){
        jsonItem["code"] = "400";
        jsonItem["message"] = "ticket is available or has already been paid";
    }
    else if(ticket_status.first.isEmpty() && ticket_status.second.isEmpty()) {
        jsonItem["code"] = "404";
        jsonItem["message"] = "ticket not found";
    }
    else {
        jsonItem["ticket_id"] = ticket_id;
        jsonItem["status"] = "success paid";
        jsonItem["win_sum"] = m_db->pay_for_ticket(ticket_id).second;
    }

    QJsonDocument jsonPayStatus_doc(jsonItem);
    QString jsonPayStatus_string = jsonPayStatus_doc.toJson();

    return jsonPayStatus_string;
}

QString JsonFormatter::process_error(QString ticket_id){
    QJsonObject jsonItem;
    QString error_message = IDhelper::checkFormatID(ticket_id);
    jsonItem["code"] = "405";
    jsonItem["message"] = error_message;

    QJsonDocument jsonError_doc(jsonItem);
    QString jsonError_string = jsonError_doc.toJson();

    return jsonError_string;
}

JsonFormatter::~JsonFormatter()
{
    m_db->~database();
}


