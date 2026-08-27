#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "txt_template_fileds_parser.h"

TemplateFieldsTxtParser::TemplateFieldsTxtParser(const QString& path, QObject *parent)
    : fieldsPath(path)
{}

QMap<QString, QStringList> TemplateFieldsTxtParser::getTemplateFieldsMap(const QStringList &docxs)
{
    QMap<QString, QStringList> result = {};

    foreach (QString docx, docxs) {
        QFile file(fieldsPath + docx + ".txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            emit TroubleWithDocx(file.filesystemFileName().c_str());
            continue;
        }

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            result[docx].append(line);
        }
        file.close();
    }
    return result;
}
