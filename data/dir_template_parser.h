#ifndef DIR_TEMPLATE_PARSER_H
#define DIR_TEMPLATE_PARSER_H

#include <QObject>
#include "../domain/repo_interfaces/i_template_repository.h"

class DirTemplateParser : public ITemplateRepository
{
    Q_OBJECT
public:
    explicit DirTemplateParser(QObject *parent = nullptr);
    QStringList getTemplates(const QString&) override;
signals:
};

#endif // DIR_TEMPLATE_PARSER_H
