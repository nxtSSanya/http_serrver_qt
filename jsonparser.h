#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QtDebug>
#include <QString>

class JsonParser
{
public:
    JsonParser(QString json_string);
    QVariantMap tree();
private:
    QString m_jsonString;
};

#endif // JSONPARSER_H
