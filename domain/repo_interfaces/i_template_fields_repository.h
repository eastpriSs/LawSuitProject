#ifndef I_TEMPLATE_FIELDS_REPOSITORY_H
#define I_TEMPLATE_FIELDS_REPOSITORY_H

#include <QObject>

class ITemplateFieldsRepository : public QObject
{
    Q_OBJECT
public:
    explicit ITemplateFieldsRepository(QObject *parent = nullptr);
    virtual QMap<QString, QStringList> getTemplateFieldsMap(const QString path, const QStringList docxs) = 0;
signals:
    void TroubleWithDoc(QString doc);
};

#endif // I_TEMPLATE_FIELDS_REPOSITORY_H
