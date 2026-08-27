#include "form_model.h"
#include <QDebug>
#include <QSet>

FormModel::FormModel(UpdateTemplateList* updTempls, UpdateTemplateFields* updFields, QObject *parent)
    : QObject{parent}, updateTemplates(updTempls), updateTemplatesFields(updFields)
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

void FormModel::onCannotUpdateFieldsForDoc(QString doc)
{
    emit errorNoteRequested(doc, "❗");
    emit appStateSwitchRequested("Функционал ограничен");
}
