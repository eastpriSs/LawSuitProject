#ifndef FILE_SAVER_H
#define FILE_SAVER_H

#include "../domain/repo_interfaces/i_file_saver_repository.h"

class FileSaver : public IFileSaverRepository
{
public:
    FileSaver() = default;
    FileSaver(const QString& s) : systemDir(s){}
    void saveFiles(QString dist, QString dirName, QList<ProccessedFile> files) override;
    void saveTemproryFiles(QList<ProccessedFile> files) override;
private:
    QString systemDir;
};

#endif // FILE_SAVER_H
