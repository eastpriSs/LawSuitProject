
#include <QDebug>
#include <QSet>

#include "form_model.h"
#include "../domain/entity/form_data_map.h"
#include "../domain/entity/lookup_list_type.h"

namespace {

void invalidate(QStringList& cache){
    cache.clear();
}

}

FormModel::FormModel(UpdateTemplateList* updTempls, UpdateTemplateFields* updFields,
                     SaveFiles* sf, LoadSuit* ls, OpenTemproryDocuments* op,
                     LoadLookupList* loadll, SaveLookupList* savell, QObject *parent)
    : QObject{parent}, updateTemplates(updTempls), updateTemplatesFields(updFields),
    saveFiles(sf), loadSuit(ls), openDocuments(op), loadList(loadll), saveList(savell)
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
{ // todo может есть вариант получше
    QSet<QString> fields;
    checkedTemplates[name] = checked;
    for (const auto& [checkedTemplate, isChecked] : checkedTemplates.asKeyValueRange()) {
        if (isChecked) {
            foreach (QString i, templatesFields[checkedTemplate]) {
                fields.insert(i);
            }
        }
    }
    emit highlightFieldsRequested(fields);
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

void FormModel::requestCourtModel()
{
    if (courtModelCache.empty())
        courtModelCache = (*loadList)(LookupListType::Court);
    emit courtModelLoaded(courtModelCache);
}

void FormModel::requestExpertModel()
{
    if (expertModelCache.empty())
        expertModelCache = (*loadList)(LookupListType::Expert);
    emit expertModelLoaded(expertModelCache);
}

void FormModel::requestExpertiseType()
{
    if (expertiseModelCache.empty())
        expertiseModelCache = (*loadList)(LookupListType::ExpertiseType);;
    emit expertiseTypeLoaded(expertiseModelCache);
}

void FormModel::saveCourtModel(const QStringList &items)
{
    invalidate(courtModelCache);
    (*saveList)(LookupListType::Court, items);
}

void FormModel::saveExpertModel(const QStringList &items)
{
    invalidate(expertModelCache);
    (*saveList)(LookupListType::Expert, items);
}

void FormModel::saveExpertiseType(const QStringList &items)
{
    invalidate(expertiseModelCache);
    (*saveList)(LookupListType::ExpertiseType, items);
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
