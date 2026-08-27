#pragma once
#include <QObject>
#include <QMap>
#include <QStringList>

class ITemplateFieldsRepository;

class UpdateTemplateFields : public QObject {
    Q_OBJECT
    ITemplateFieldsRepository* repo;

public:
    explicit UpdateTemplateFields(ITemplateFieldsRepository* r, QObject *parent = nullptr);
    QMap<QString, QStringList> operator()(const QStringList &docxs);

signals:
    void CannotUpdateFieldsForDoc(QString docx);

private slots:
    void onTroubleWithDoc(QString docx);
};
