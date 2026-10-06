#ifndef I_DOCUMENT_OPENER_REPOSITORY_H
#define I_DOCUMENT_OPENER_REPOSITORY_H

#include <QObject>
#include "../entity/proccessed_file.h"

class IDocumentOpenerRepository : public QObject
{
    Q_OBJECT
public:
    explicit IDocumentOpenerRepository(QObject *parent = nullptr);
    virtual void open(QList<ProccessedFile> files) = 0;
signals:
};

#endif // I_DOCUMENT_OPENER_REPOSITORY_H
