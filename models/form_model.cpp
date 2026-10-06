
#include <QDebug>
#include <QSet>

#include "form_model.h"
#include "../domain/entity/form_data_map.h"

FormModel::FormModel(UpdateTemplateList* updTempls, UpdateTemplateFields* updFields,
                     SaveFiles* sf, LoadSuit* ls, OpenTemproryDocuments* op, QObject *parent)
    : QObject{parent}, updateTemplates(updTempls), updateTemplatesFields(updFields), saveFiles(sf), loadSuit(ls), openDocuments(op)
{
    connect(updateTemplatesFields, &UpdateTemplateFields::CannotUpdateFieldsForDoc,
            this, &FormModel::onCannotUpdateFieldsForDoc);
    connect(updateTemplates, &UpdateTemplateList::pathError,
            this, &FormModel::onPathError);
    connect(updateTemplates, &UpdateTemplateList::templatesError,
            this, &FormModel::onTemplatesError);
    connect(loadSuit, &LoadSuit::SuitLoaded,
            this, &FormModel::onSuitLoaded);
}

void FormModel::templatesRequested()
{
    QStringList templates = (*updateTemplates)();

    foreach (QString i, templates) {
        checkedTemplates.insert(i, false);
    }
    emit templatesGot(templates);
    templatesFields = (*updateTemplatesFields)(templates);
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

void FormModel::loadRequested(QString file)
{
    (*loadSuit)(file);
}

void FormModel::openRequested(QStringList files, const QVariantMap &formData)
{
    FormDataMap map;
    map.parse(formData);
    qInfo() << "Open requested to " << " with " << files;
    (*openDocuments)(files, map);
}

void FormModel::onPathError(QString p)
{
    emit errorMasseageRequested("Загрузка полей", "Путь к полям неверен: " + p);
    emit appStateSwitchRequested("Функционал ограничен");
}

void FormModel::onTemplatesError(QString err)
{
    emit errorMasseageRequested("Загрузка шаблонов", "Произошла ошибка при загрузке шаблонов: " + err);
    emit appStateSwitchRequested("Функционал ограничен");
}

void FormModel::onSuitLoaded(FormDataMap suitData)
{
    emit suitDataLoaded(suitData.raw());
}

void FormModel::onCannotUpdateFieldsForDoc(QString doc)
{
    emit errorNoteRequested(doc, "❗");
    emit appStateSwitchRequested("Функционал ограничен");
}
