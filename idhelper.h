#ifndef IDHELPER_H
#define IDHELPER_H

#include <QString>
#include <QRegExp>
#include <QStringList>

namespace IDhelper {
    inline QString checkFormatID(QString ticket_id) {
        bool is_letter_found = false;
        if(ticket_id.size() != 8){
            return "invalid id found with size " + QString::number(ticket_id.size()) + " when 8 need";
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

    inline QString getIDTicket(QString url)
    {
        QRegExp split_url_by_slash("/");
        QStringList splittedString = url.split(split_url_by_slash);

        QString result_id = "";

        result_id = splittedString.last();
        return result_id;
    }
}
#endif // IDHELPER_H