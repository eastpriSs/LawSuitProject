#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QSaveFile>
#include "json_lookup_list_repository.h"


namespace {

QString getTargetField(LookupListType type)
{
    QString targetField;
    switch (type) {
    case LookupListType::ExpertiseType:
        targetField = "expertise";
        break;
    case LookupListType::Expert:
        targetField = "expert";
        break;
    case LookupListType::Court:
        targetField = "court";
        break;
    }
    return targetField;
}


}

JsonLookupListRepository::JsonLookupListRepository(const QString &cfgf)
    : cfgFile(cfgf)
{
}

QStringList JsonLookupListRepository::load(LookupListType type) const
{
    QString targetField = getTargetField(type);
    QFile file(cfgFile);
    QJsonArray array;
    if (file.open(QFile::ReadOnly)) {
        QJsonDocument cfgJson = QJsonDocument::fromJson(file.readAll());
        QJsonObject obj = cfgJson.object();
        array = obj[targetField].toArray();
    }
    QStringList result;
    for (const QJsonValue &val : array) {
        if (val.isString()) {
            result.append(val.toString());
        }
    }
    qInfo() << "Loaded:" << result;
    return result;
}

bool JsonLookupListRepository::save(LookupListType type, const QStringList &items)
{
    const QString targetField = getTargetField(type);
    QJsonObject root;
    QFile inFile(cfgFile);
    if (inFile.exists()) {
        if (!inFile.open(QFile::ReadOnly)) {
            qWarning() << "JsonLookupListRepository: cannot open for read:" << cfgFile
                       << inFile.errorString();
            return false;
        }
        QJsonParseError parseErr;
        const QJsonDocument doc = QJsonDocument::fromJson(inFile.readAll(), &parseErr);
        inFile.close();

        if (parseErr.error != QJsonParseError::NoError) {
            qWarning() << "JsonLookupListRepository: JSON parse error in" << cfgFile
                       << parseErr.errorString();
            return false;
        }
        if (!doc.isObject()) {
            qWarning() << "JsonLookupListRepository: root is not an object:" << cfgFile;
            return false;
        }
        root = doc.object();
    }

    QJsonArray arr;
    for (const QString &s : items)
        arr.append(s);
    root[targetField] = arr;

    QSaveFile outFile(cfgFile);
    if (!outFile.open(QFile::WriteOnly | QFile::Truncate)) {
        qWarning() << "JsonLookupListRepository: cannot open for write:" << cfgFile
                   << outFile.errorString();
        return false;
    }
    outFile.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    if (!outFile.commit()) {
        qWarning() << "JsonLookupListRepository: commit failed:" << cfgFile
                   << outFile.errorString();
        return false;
    }
    return true;
}
