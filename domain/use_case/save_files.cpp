#include "save_files.h"
#include "../entity/proccessed_file.h"

SaveFiles::SaveFiles(IFileSaverRepository *r,
                     IFilesProccessorRepository *p,
                     IRecoveryFileMaker *recoveryMaker,
                     QObject *parent)
    : QObject{parent},
    fileStorage(r),
    fileProccessor(p),
    recoveryFileMaker(recoveryMaker)
{}

void SaveFiles::operator()(QString dist, QStringList files, const FormDataMap &formData)
{
    QList<ProccessedFile> prcFiles;
    for (const QString &file : files) {
        prcFiles.append(fileProccessor->proccess(file, formData));
    }
    prcFiles.append(recoveryFileMaker->make(formData));

    const QString savingPath = makeDirName(formData);
    fileStorage->saveFiles(dist, savingPath, prcFiles);
}

QString SaveFiles::makeDirName(const FormDataMap &formData) const
{
    return QString("%1_%2").arg(
        formData.getData().main.caseID,
        formData.getData().main.caseName
        );
}
