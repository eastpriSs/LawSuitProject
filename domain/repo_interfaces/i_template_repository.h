#ifndef I_TEMPLATE_REPOSITORY_H
#define I_TEMPLATE_REPOSITORY_H

#include <QObject>

class ITemplateRepository : public QObject
{
    Q_OBJECT
public:
    explicit ITemplateRepository(QObject *parent = nullptr);
    virtual QStringList getTemplates() = 0;
    virtual ~ITemplateRepository() = default;
signals:
};

#endif // I_TEMPLATE_REPOSITORY_H
