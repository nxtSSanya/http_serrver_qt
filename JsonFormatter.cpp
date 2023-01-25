#include "JsonFormatter.h"

JsonFormatter::JsonFormatter()
{

}


QString JsonFormatter::JsonGetIdOfTickets(const std::vector<QString>& tickets_list)
{
    QJsonObject jsonItem;
    QJsonArray jsonIdArray;

    for(auto&i:tickets_list){
        jsonItem["ticket_id"] = i;
        jsonIdArray.append(jsonItem);
    }

    QJsonDocument jsonId_doc(jsonIdArray);
    QString jsonId_string = jsonId_doc.toJson();

    return jsonId_string;
}

QString JsonFormatter::JsonGetStatusById(const std::pair<QString, QString>& ticket_status)
{
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

QString JsonFormatter::JsonSellTicket(const std::pair<QString, QString>& ticket_status)
{
    QJsonObject jsonItem;

    if(ticket_status.second == "paid" || ticket_status.second == "sold"){
        jsonItem["code"] = "400";
        jsonItem["message"] = "ticket has already been sold or paid";
    }
    else if(ticket_status.first.isEmpty() || ticket_status.second.isEmpty()) {
        jsonItem["code"] = "404";
        jsonItem["message"] = "ticket not found";
    }
    else {
        jsonItem["ticket_id"] = ticket_status.first;
        jsonItem["status"] = ticket_status.second;
    }

    QJsonDocument jsonSellStatus_doc(jsonItem);
    QString jsonSellStatus_string = jsonSellStatus_doc.toJson();

    return jsonSellStatus_string;
}

QString JsonFormatter::JsonPayForTicket(const std::pair<QString, QString>& ticket_status)
{
    QJsonObject jsonItem;

    if(ticket_status.second == "paid" || ticket_status.second == "available"){
        jsonItem["code"] = "400";
        jsonItem["message"] = "ticket is available or has already been paid";
    }
    else if(ticket_status.first.isEmpty() || ticket_status.second.isEmpty()) {
        jsonItem["code"] = "404";
        jsonItem["message"] = "ticket not found";
    }
    else {
        jsonItem["ticket_id"] = ticket_status.first;
        jsonItem["status"] = "success paid";
        jsonItem["win_sum"] = ticket_status.second;
    }

    QJsonDocument jsonPayStatus_doc(jsonItem);
    QString jsonPayStatus_string = jsonPayStatus_doc.toJson();

    return jsonPayStatus_string;
}

QString JsonFormatter::JsonProcessError(const QString& ticket_id){
    QJsonObject jsonItem;
    QString error_message = IDhelper::checkFormatID(ticket_id);
    jsonItem["code"] = "405";
    jsonItem["message"] = error_message;

    QJsonDocument jsonError_doc(jsonItem);
    QString jsonError_string = jsonError_doc.toJson();

    return jsonError_string;
}




