#ifndef IDHELPER_H
#define IDHELPER_H

#include <QString>
#include <QRegExp>
#include <QStringList>

#include "ConfigReader.h"


namespace IDhelper {
    inline QString checkFormatID(const QString& ticket_id) {

        ConfigReader reader(config_file_path);
        if(!reader.error().isEmpty()) {
            std::cout << reader.error().toStdString() << "\n";
            std::cout << "ticket id by defaul: " << reader.getServerTicketSize() << "\n";
        }
        int ticket_size = reader.getServerTicketSize();

        bool is_letter_found = false;
        if(ticket_id.size() != ticket_size){
            return "invalid id found with size " + QString::number(ticket_id.size()) + " when " + QString::number(ticket_size) + " need";
        }
        for(auto&i: ticket_id){
            if(!i.isDigit()){
                is_letter_found = true;
            }
        }
        if(is_letter_found){
            return "invalid id found letters";
        }

        return "OK";
    }

    inline QString getIDTicket(const QString& url)
    {
        QRegExp split_url_by_slash("/");
        QStringList splittedString = url.split(split_url_by_slash);

        QString result_id = "";

        result_id = splittedString.last();
        return result_id;
    }
}
#endif // IDHELPER_H
