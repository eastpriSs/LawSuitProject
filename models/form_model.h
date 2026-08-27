#ifndef FORM_MODEL_H
#define FORM_MODEL_H

#include <QObject>
#include <QMap>
#include <QSet>
#include "../domain/use_case/update_template_list.h"
#include "../domain/use_case/update_template_fields.h"

class FormModel : public QObject {
    Q_OBJECT
public:
    explicit FormModel(UpdateTemplateList* updTempls, UpdateTemplateFields* updFields, QObject *parent = nullptr);
    void templatesRequested();

signals:
    void templatesGot(QStringList templates);
    void highlightFieldsRequested(QSet<QString> fields);
    void errorNoteRequested(QString name, QString note);
    void errorMasseageRequested(const QString& title, const QString& discription);
    void appStateSwitchRequested(QString state);

public slots:
    void templateChecked(const QString &name, bool checked);

private slots:
    void onCannotUpdateFieldsForDoc(QString doc);
    void onPathError(QString p);
    void onTemplatesError(QString err);

private:
    UpdateTemplateList* updateTemplates;
    UpdateTemplateFields* updateTemplatesFields;
    QMap<QString, QStringList> templatesFields;
    QMap<QString, bool> checkedTemplates;
};

#endif // FORM_MODEL_H
