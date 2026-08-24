#ifndef FORM_MODEL_H
#define FORM_MODEL_H

#include <QObject>
#include <QMap>
#include "../domain/use_case/update_template_list.h"
#include "../domain/use_case/update_template_fields.h"

class FormModel : public QObject
{
    Q_OBJECT
public:
    explicit FormModel(UpdateTemplateList* updTempls, UpdateTemplateFields* updFields, QObject *parent = nullptr);
    void templatesRequested();

signals:
    void templatesGot(QStringList templates);
    void highlightFieldsRequested(QStringList fields);

public slots:
    void templateChecked(const QString &name, bool checked);

private:
    UpdateTemplateList* updateTemplates;
    UpdateTemplateFields* updateTemplatesFields;
    QMap<QString, QStringList> templatesFields;
    QMap<QString, bool> checkedTemplates;
};

#endif // FORM_MODEL_H
