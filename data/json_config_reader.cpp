#include "json_config_reader.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

AppConfig JsonConfigReader::loadConfig() {
    AppConfig config;
    QFile file("config.json");
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonObject obj = doc.object();
        config.templatesPath = obj["templatesPath"].toString();
        config.fieldsPath = obj["fieldsPath"].toString();
    }
    return config;
}
