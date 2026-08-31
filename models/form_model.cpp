
#include <QDebug>
#include <QSet>

#include "form_model.h"
#include "../domain/entity/form_data_map.h"

FormModel::FormModel(UpdateTemplateList* updTempls, UpdateTemplateFields* updFields, SaveFiles* sf, QObject *parent)
    : QObject{parent}, updateTemplates(updTempls), updateTemplatesFields(updFields), saveFiles(sf)
{
    connect(updateTemplatesFields, &UpdateTemplateFields::CannotUpdateFieldsForDoc,
            this, &FormModel::onCannotUpdateFieldsForDoc);
    connect(updateTemplates, &UpdateTemplateList::pathError,
            this, &FormModel::onPathError);
    connect(updateTemplates, &UpdateTemplateList::templatesError,
            this, &FormModel::onTemplatesError);

}
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
    if (checked) {
        QSet<QString> fields;
        foreach (QString i, templatesFields[name]) {
            fields.insert(i);
        }
        emit highlightFieldsRequested(fields);
    }
}

void FormModel::saveRequested(QString dist, QStringList files, const QVariantMap &formData)
{
    FormDataMap map;
    map.parse(formData);
    qInfo() << "Save requested to " << dist << " with " << files;
    (*saveFiles)(dist, files, map);
}

void FormModel::onPathError(QString p)
{
    errorMasseageRequested("Загрузка полей", "Путь к полям неверен: " + p);
    emit appStateSwitchRequested("Функционал ограничен");
}

void FormModel::onTemplatesError(QString err)
{
    errorMasseageRequested("Загрузка шаблонов", "Произошла  ошибка при загрузки шаблонов: " + err);
    emit appStateSwitchRequested("Функционал ограничен");
}

void FormModel::onCannotUpdateFieldsForDoc(QString doc)
{
    emit errorNoteRequested(doc, "❗");
    emit appStateSwitchRequested("Функционал ограничен");
}
