#include "open_temprory_documents.h"
#include "../entity/proccessed_file.h"

OpenTemproryDocuments::OpenTemproryDocuments(IFilesProccessorRepository *prc, IFileSaverRepository *s, IDocumentOpenerRepository* op, QObject *parent)
    : fileProccessor(prc), saver(s), opener(op), QObject{parent}
{
}

void OpenTemproryDocuments::operator()(QStringList files, const FormDataMap& formData)
{
    QList<ProccessedFile> prcFiles;
    for (const QString &file : files) {
        prcFiles.append(fileProccessor->proccess(file, formData));
    }
    saver->saveTemproryFiles(prcFiles);
    opener->open(prcFiles);
}
