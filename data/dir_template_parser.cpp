#include <QDir>
#include <QDebug>
#include "dir_template_parser.h"


[[nodiscard]] QStringList DirTemplateParser::getTemplates()
{
    QDir dir(templatesPath);
    QStringList filters;
    filters << "*.docx" << "*.doc";
    dir.setNameFilters(filters);

    QStringList files = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    return files;
}

DirTemplateParser::DirTemplateParser(const QString &path, QObject *parent)
    : templatesPath(path)
{
}
