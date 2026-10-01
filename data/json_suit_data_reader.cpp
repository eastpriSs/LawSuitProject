#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include "json_suit_data_reader.h"

QByteArray JsonSuitDataReader::readFile(const QString& path) const
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) {
        qWarning() << "Cannot open file for reading:" << path;
        return {};
    }
    return f.readAll();
}

bool JsonSuitDataReader::exists(const QString& path) const
{
    return QFileInfo::exists(path);
}
