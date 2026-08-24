#include "form_model.h"
#include <QDebug>

FormModel::FormModel(UpdateTemplateList* updTempls, UpdateTemplateFields* updFields, QObject *parent)
    : QObject{parent}, updateTemplates(updTempls), updateTemplatesFields(updFields)
{}

void FormModel::templatesRequested()
{
    QString testDir = "/home/eastpris/LawsuitProject/templates/";
    QStringList templates = (*updateTemplates)(testDir);
    foreach (QString i, templates) {
        checkedTemplates.insert(i, false);
    }
    emit templatesGot(templates);
    templatesFields = (*updateTemplatesFields)("/home/eastpris/LawsuitProject/settings/fileds_to_fill/", templates);
    qInfo() << templatesFields;
}

void FormModel::templateChecked(const QString &name, bool checked)
{
    checkedTemplates[name] = checked;
}
