#include "../entity/path.h"
#include "../repo_interfaces/i_template_repository.h"
#include "update_template_list.h"

UpdateTemplateList::UpdateTemplateList(ITemplateRepository* repo, QObject *parent)
    : repo(repo), QObject{parent}
{}

QStringList UpdateTemplateList::operator()(const QString &path)
{
    QStringList templates;
    try {
        Path p(path.toStdString());
        templates = repo->getTemplates(QString::fromStdString(p.value()));

        if (templates.empty()) emit templatesError("Ни один шаблон не был загружен.");

    } catch (const std::invalid_argument& errPath) {
        emit pathError("Путь к шаблоном указан неверно. Возможно, файл конфигурации был поврежден.");
    }

    return templates;
}
