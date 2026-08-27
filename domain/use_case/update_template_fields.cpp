// domain/use_case/update_template_fields.cpp
#include "update_template_fields.h"
#include "../repo_interfaces/i_template_fields_repository.h"
#include <QDebug>

UpdateTemplateFields::UpdateTemplateFields(ITemplateFieldsRepository* r, QObject *parent)
    : QObject{parent}, repo(r)
{
    connect(repo, &ITemplateFieldsRepository::TroubleWithDocx, this, &UpdateTemplateFields::onTroubleWithDoc);
}

QMap<QString, QStringList> UpdateTemplateFields::operator()(const QStringList &docxs)
{
    return repo->getTemplateFieldsMap(docxs);
}

void UpdateTemplateFields::onTroubleWithDoc(QString docx)
{
    qInfo() << "Trouble with " << docx;
    emit CannotUpdateFieldsForDoc(docx);
}
