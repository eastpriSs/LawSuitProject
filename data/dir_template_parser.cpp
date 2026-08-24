#include <QDir>
#include <QDebug>
#include "dir_template_parser.h"

DirTemplateParser::DirTemplateParser(QObject *parent)
    : ITemplateRepository{parent}
{}


[[nodiscard]] QStringList DirTemplateParser::getTemplates(const QString & path)
{
    QDir dir(path);
    QStringList filters;
    filters << "*.docx" << "*.doc";
    dir.setNameFilters(filters);

    QStringList files = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    return files;
}
