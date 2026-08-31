#ifndef I_FILES_PROCCESSOR_REPOSITORY_H
#define I_FILES_PROCCESSOR_REPOSITORY_H

#include <QObject>
#include "../entity/proccessed_file.h"
#include "../entity/form_data_map.h"

class IFilesProccessorRepository : public QObject
{
    Q_OBJECT
public:
    explicit IFilesProccessorRepository(QObject *parent = nullptr);
    virtual ProccessedFile proccess(const QString& file, const FormDataMap& data ) = 0;
signals:
};

#endif // I_FILES_PROCCESSOR_REPOSITORY_H
