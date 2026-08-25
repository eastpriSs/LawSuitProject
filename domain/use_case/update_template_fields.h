#ifndef UPDATE_TEMPLATE_FIELDS_H
#define UPDATE_TEMPLATE_FIELDS_H

#include <QObject>
#include <QMap>

class ITemplateFieldsRepository;
class UpdateTemplateFields : public QObject
{
    Q_OBJECT
public:
    explicit UpdateTemplateFields(ITemplateFieldsRepository* r, QObject *parent = nullptr);
    QMap<QString, QStringList> operator()(const QString& path, const QStringList& docxs);

private slots:
    void onTroubleWithDoc(QString docx);

private:
    ITemplateFieldsRepository* repo;

signals:
    void CannotUpdateFieldsForDoc(QString docx);
};

#endif // UPDATE_TEMPLATE_FIELDS_H
