#ifndef TXT_TEMPLATE_FILEDS_PARSER_H
#define TXT_TEMPLATE_FILEDS_PARSER_H

#include <QObject>
#include <QMap>
#include "../domain/repo_interfaces/i_template_fields_repository.h"

class TemplateFieldsTxtParser : public ITemplateFieldsRepository
{
    Q_OBJECT
public:
    explicit TemplateFieldsTxtParser(QObject *parent = nullptr);
    QMap<QString, QStringList> getTemplateFieldsMap(const QString path, const QStringList docxs) override;

signals:
};

#endif // TXT_TEMPLATE_FILEDS_PARSER_H
