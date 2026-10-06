#ifndef OPEN_TEMPRORY_DOCUMENTS_H
#define OPEN_TEMPRORY_DOCUMENTS_H

#include <QObject>
#include "../repo_interfaces/i_files_proccessor_repository.h"
#include "../repo_interfaces/i_file_saver_repository.h"
#include "../repo_interfaces/i_document_opener_repository.h"

class OpenTemproryDocuments : public QObject
{
    Q_OBJECT
public:
    explicit OpenTemproryDocuments(IFilesProccessorRepository* prc, IFileSaverRepository* s, IDocumentOpenerRepository* op, QObject *parent = nullptr);
    void operator()(QStringList files, const FormDataMap& data);

signals:
private:
    IFilesProccessorRepository* fileProccessor;
    IFileSaverRepository* saver;
    IDocumentOpenerRepository* opener;
};

#endif // OPEN_TEMPRORY_DOCUMENTS_H
