#ifndef FILE_SAVER_H
#define FILE_SAVER_H

#include "../domain/repo_interfaces/i_file_saver_repository.h"

class FileSaver : public IFileSaverRepository
{
public:
    FileSaver() = default;
    void saveFiles(QString dist, QList<ProccessedFile> files) override;
};

#endif // FILE_SAVER_H
