#include "save_files.h"
#include "../entity/proccessed_file.h"

SaveFiles::SaveFiles(IFileSaverRepository *r, IFilesProccessorRepository *p, QObject *parent)
    : QObject{parent}, fileStorage(r), fileProccessor(p)
{}

void SaveFiles::operator()(QString dist, QStringList files, const FormDataMap &formData)
{
    QList<ProccessedFile> prcFiles;
    foreach (QString file, files) {
        prcFiles.append(fileProccessor->proccess(file, formData));
    }
    fileStorage->saveFiles(dist, prcFiles);
}
