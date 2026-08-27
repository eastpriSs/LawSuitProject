#include "update_template_list.h"
#include "../repo_interfaces/i_template_repository.h"

UpdateTemplateList::UpdateTemplateList(ITemplateRepository* repo, QObject *parent)
    : repo(repo), QObject{parent}
{}

QStringList UpdateTemplateList::operator()()
{
    QStringList templates = repo->getTemplates();
    if (templates.empty()) emit templatesError("Ни один шаблон не был загружен.");

    return templates;
}
