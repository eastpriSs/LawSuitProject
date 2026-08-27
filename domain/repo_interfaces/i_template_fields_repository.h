#pragma once
#include <QMap>
#include <QObject>
#include <QStringList>

class ITemplateFieldsRepository : public QObject {
    Q_OBJECT
public:
    virtual ~ITemplateFieldsRepository() = default;
    virtual QMap<QString, QStringList> getTemplateFieldsMap(const QStringList &docxs) = 0;
signals:
    void TroubleWithDocx(QString docx);
};
