#include "../entity/path.h"
#include "../repo_interfaces/i_template_repository.h"
#include "update_template_list.h"

UpdateTemplateList::UpdateTemplateList(ITemplateRepository* repo, QObject *parent)
    : repo(repo), QObject{parent}
{}

QStringList UpdateTemplateList::operator()(const QString &path)
{
    Path p(path.toStdString());
    QStringList templates = repo->getTemplates(QString::fromStdString(p.value()));
    return templates;
}
