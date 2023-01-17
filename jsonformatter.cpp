#include "jsonformatter.h"

JsonFormatter::JsonFormatter()
{
    m_db = new database("localhost", "db_lottery", "root", "Hellokisa228!");
}

QString JsonFormatter::getJsonString() {
    QJsonObject json_obj;
    json_obj["ticket_id"] = "00000001";
    json_obj["status"] = "available";

    QJsonDocument json_doc(json_obj);
    QString json_string = json_doc.toJson();

    return json_string;
}

QString JsonFormatter::getIdValues()
{
    std::vector<QString> id_vec = m_db->getIdArray();
    QJsonObject jsonItem;
    QJsonArray jsonIdArray;

    for(auto&i:id_vec){
        jsonItem["ticket_id"] = i;
        jsonIdArray.append(jsonItem);
    }

    QJsonDocument jsonId_doc(jsonIdArray);
    QString jsonId_string = jsonId_doc.toJson();

    m_db->~database();
    return jsonId_string;
}

QString JsonFormatter::getStatusById(QString ticket_id)
{
    std::pair<QString, QString> ticket_status = m_db->findById(ticket_id);
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

    m_db->~database();
    return jsonTicketInfo_string;
}

QString JsonFormatter::updateTicketStatus(QString ticket_id)
{
    QJsonObject jsonItem;

    jsonItem["ticket_id"] = ticket_id;
    jsonItem["status"] = m_db->sellTicket(ticket_id);

    QJsonDocument jsonSellStatus_doc(jsonItem);
    QString jsonSellStatus_string = jsonSellStatus_doc.toJson();

    m_db->~database();
    return jsonSellStatus_string;
}


