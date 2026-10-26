#ifndef FORM_MODEL_H
#define FORM_MODEL_H

#include <QObject>
#include <QMap>
#include <QSet>
#include "../domain/use_case/update_template_list.h"
#include "../domain/use_case/update_template_fields.h"
#include "../domain/use_case/save_files.h"
#include "../domain/use_case/load_suit.h"
#include "../domain/use_case/open_temprory_documents.h"
#include "../domain/use_case/load_lookup_list.h"
#include "../domain/use_case/save_lookup_list.h"

class FormModel : public QObject {
    Q_OBJECT
public:
    explicit FormModel(UpdateTemplateList* updTempls, UpdateTemplateFields* updFields,
                       SaveFiles* sf, LoadSuit* ls, OpenTemproryDocuments* op,
                       LoadLookupList* loadll, SaveLookupList* savell, QObject *parent = nullptr);
    void templatesRequested();

signals:
    void templatesGot(QStringList templates);
    void highlightFieldsRequested(QSet<QString> fields);
    void errorNoteRequested(QString name, QString note);
    void errorMasseageRequested(const QString& title, const QString& discription);
    void appStateSwitchRequested(QString state);
    void suitDataLoaded(QVariantMap formData);

    void courtModelLoaded(const QStringList &items);
    void expertModelLoaded(const QStringList &items);
    void expertiseTypeLoaded(const QStringList &items);

public slots:
    void templateChecked(const QString &name, bool checked);
    void saveRequested(QString dist, QStringList files, const QVariantMap &formData);
    void loadRequested(QString file);
    void openRequested(QStringList files, const QVariantMap &formData);

    void requestCourtModel();
    void requestExpertModel();
    void requestExpertiseType();

    void saveCourtModel(const QStringList &items);
    void saveExpertModel(const QStringList &items);
    void saveExpertiseType(const QStringList &items);

private slots:
    void onCannotUpdateFieldsForDoc(QString doc);
    void onPathError(QString p);
    void onTemplatesError(QString err);
    void onSuitLoaded(FormDataMap);

private:
    QMap<QString, QStringList> templatesFields;
    QMap<QString, bool> checkedTemplates;
    UpdateTemplateList* updateTemplates;
    UpdateTemplateFields* updateTemplatesFields;
    LoadSuit* loadSuit;
    SaveFiles* saveFiles;
    OpenTemproryDocuments* openDocuments;
    LoadLookupList* loadList;
    SaveLookupList* saveList;
};

#endif // FORM_MODEL_H
