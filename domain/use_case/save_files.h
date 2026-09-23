#ifndef SAVE_FILES_H
#define SAVE_FILES_H

#include <QObject>
#include "../repo_interfaces/i_file_saver_repository.h"
#include "../repo_interfaces/i_files_proccessor_repository.h"
#include "../entity/form_data_map.h"

class SaveFiles : public QObject
{
    Q_OBJECT
public:
    explicit SaveFiles(IFileSaverRepository* r, IFilesProccessorRepository* p, QObject *parent = nullptr);
    void operator()(QString dist, QStringList files, const FormDataMap& formData);
private:
    QString makeDirName(const FormDataMap& formData) const;

signals:
private:
    IFileSaverRepository* fileStorage;
    IFilesProccessorRepository* fileProccessor;
};

#endif // SAVE_FILES_H
