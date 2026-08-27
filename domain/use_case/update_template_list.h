#ifndef UPDATE_TEMPLATE_LIST_H
#define UPDATE_TEMPLATE_LIST_H

#include <QObject>
#include <QStringList>

class ITemplateRepository;

class UpdateTemplateList : public QObject {
    Q_OBJECT
    ITemplateRepository* repo;

public:
    explicit UpdateTemplateList(ITemplateRepository* repo, QObject *parent = nullptr);
    QStringList operator()();

signals:
    void pathError(QString p);
    void templatesError(QString err);
};

#endif // UPDATE_TEMPLATE_LIST_H
