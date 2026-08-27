#ifndef DIR_TEMPLATE_PARSER_H
#define DIR_TEMPLATE_PARSER_H

#include <QObject>
#include "../domain/repo_interfaces/i_template_repository.h"

class DirTemplateParser : public ITemplateRepository
{
    Q_OBJECT
    QString templatesPath;
public:
    explicit DirTemplateParser(const QString& path, QObject *parent = nullptr);
    QStringList getTemplates() override;
signals:
};

#endif // DIR_TEMPLATE_PARSER_H
