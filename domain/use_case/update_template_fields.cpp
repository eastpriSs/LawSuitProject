#include <QDebug>
#include "update_template_fields.h"
#include "../repo_interfaces/i_template_fields_repository.h"
#include "../entity/path.h"

UpdateTemplateFields::UpdateTemplateFields(ITemplateFieldsRepository* r, QObject *parent)
    : QObject{parent}, repo(r)
{
    connect(repo, &ITemplateFieldsRepository::TroubleWithDoc, this, &UpdateTemplateFields::onTroubleWithDoc);
}

QMap<QString, QStringList> UpdateTemplateFields::operator()(const QString &path, const QStringList &docxs)
{
    Path p(path.toStdString());
    return repo->getTemplateFieldsMap(QString::fromStdString(p.value()), docxs);
}

void UpdateTemplateFields::onTroubleWithDoc(QString docx)
{
    qInfo() << "Trouble with " << docx;
    emit CannotUpdateFieldsForDoc(docx);
}
