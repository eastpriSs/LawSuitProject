#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include "txt_template_fileds_parser.h"

TemplateFieldsTxtParser::TemplateFieldsTxtParser(QObject *parent)
    : ITemplateFieldsRepository{parent}
{}

QMap<QString, QStringList> TemplateFieldsTxtParser::getTemplateFieldsMap(const QString path, const QStringList docxs)
{
    QMap<QString, QStringList> result;

    foreach (QString docx, docxs)
    {
        QFile file(path + docx + ".txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            // todo
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
