#ifndef UPDATE_TEMPLATE_LIST_H
#define UPDATE_TEMPLATE_LIST_H

#include <QObject>

class ITemplateRepository;
class UpdateTemplateList : public QObject
{
    Q_OBJECT
public:
    explicit UpdateTemplateList(ITemplateRepository* repo, QObject *parent = nullptr);
    QStringList operator()(const QString& path);
private:
    ITemplateRepository* repo;
signals:
    void pathError(QString p);
    void templatesError(QString err);
};

#endif // UPDATE_TEMPLATE_LIST_H
