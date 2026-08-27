#ifndef TXT_TEMPLATE_FILEDS_PARSER_H
#define TXT_TEMPLATE_FILEDS_PARSER_H

#include <QObject>
#include <QMap>
#include "../domain/repo_interfaces/i_template_fields_repository.h"

class TemplateFieldsTxtParser : public ITemplateFieldsRepository {
    Q_OBJECT
    QString fieldsPath;

public:
    explicit TemplateFieldsTxtParser(const QString& path, QObject *parent = nullptr);
    QMap<QString, QStringList> getTemplateFieldsMap(const QStringList &docxs) override;
};

#endif // TXT_TEMPLATE_FILEDS_PARSER_H
