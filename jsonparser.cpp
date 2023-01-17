#include "jsonparser.h"


JsonParser::JsonParser(QString json_string) : m_jsonString(json_string) { }

QVariantMap JsonParser::tree() {
    QByteArray json_bytes = m_jsonString.toLocal8Bit();

    auto json_doc = QJsonDocument::fromJson(json_bytes);
    QJsonObject json_obj = json_doc.object();

    QVariantMap json_map = json_obj.toVariantMap();

    return json_map;
}

