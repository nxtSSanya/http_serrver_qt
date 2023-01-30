#include "Database.h"
#include "QSqlError"

Database::Database()
{
    m_isQueryDone = false;
    m_db = QSqlDatabase::addDatabase("QSQLITE"); // QMYSQL = MARIADB
    m_db.setDatabaseName("./qwe.db");
    if(m_db.open()){
        std::cout << "Opened successfully\n";
    }
    else{
        std::cout << "Error while opening\n";
    }
}

Database::Database(Database &other)
{
    m_db = other.m_db;
    m_query = other.m_query;
    m_error = other.m_error;
    m_isQueryDone = other.m_isQueryDone;
}

bool Database::processQuery(const QString& query)
{
    m_isQueryDone = false;
    m_query = std::make_shared<QSqlQuery>(m_db);
    if(m_query->exec(query)){
        m_isQueryDone = true;
        return true;
    }
    else {
        std::cout << query.toStdString();
        std::cout << m_query->lastError().text().toStdString();
        m_error = m_query->lastError().text();
        return false;
    }
}

QString Database::error()
{
    return m_error;
}

bool Database::getDoneInfo()
{
    return m_isQueryDone;
}

std::vector<QString> Database::getIdOfTickets()
{
    std::vector<QString> id_values;
    processQuery("select ticket_id from TICKETS;");
    while(m_query->next()){
        id_values.push_back(m_query->value(0).toString());
    }
    return id_values;
}

std::pair<QString, QString> Database::findTicketById(const QString& ticket_id)
{
    m_isQueryDone = false;
    std::pair<QString, QString> ticketID_status;
    processQuery("select ticket_id, ticket_status from TICKETS where ticket_id = \"" + ticket_id + "\";");

    while(m_query->next()){
        ticketID_status.first = m_query->value(0).toString();
        ticketID_status.second = m_query->value(1).toString();
    }
    return ticketID_status;
}

std::pair<QString, QString> Database::sellTicket(const QString& ticket_id)
{
    std::pair<QString, QString> result_id_status = findTicketById(ticket_id);

    if(result_id_status.second == "available") {
        if(processQuery("update TICKETS set ticket_status = \"sold\" where ticket_id = \"" + ticket_id + "\";")) {
            result_id_status.first = ticket_id;
            result_id_status.second = "success sold";
        }
    }
    return result_id_status;
}

std::pair<QString, QString> Database::payForTicket(const QString& ticket_id)
{
    std::pair<QString, QString> result_id_winsize = findTicketById(ticket_id);

    if(result_id_winsize.second == "sold"){
//        if(processQuery("START TRANSACTION; \
//                        update TICKETS set ticket_status = \"paid\" where ticket_id = \"" + ticket_id + "\"; \
//                        select win_size from TICKETS where ticket_id = " + ticket_id + "; \
//                        COMMIT;"))
        if(processQuery("update TICKETS set ticket_status = \"paid\" where ticket_id = \"" + ticket_id + "\";") &&
               processQuery("select win_size from TICKETS where ticket_id = \"" + ticket_id + "\";"))
        {
            m_query->first();
            result_id_winsize.first = ticket_id;
            result_id_winsize.second = m_query->value(0).toString();
        }
    }
    return result_id_winsize;

}
Database::~Database()
{
    m_db.close();
}
