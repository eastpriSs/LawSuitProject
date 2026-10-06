#ifndef DOCUMENT_OPENER_H
#define DOCUMENT_OPENER_H

#include <QObject>
#include "../domain/entity/proccessed_file.h"
#include "../domain/repo_interfaces/i_document_opener_repository.h"

class DocumentOpener : public IDocumentOpenerRepository
{
public:
    explicit DocumentOpener(const QString& sd);
    void open(QList<ProccessedFile> files) override;
signals:
private:
    QString systemDir;
};

#endif // DOCUMENT_OPENER_H
