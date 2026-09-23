#ifndef I_FILE_SAVER_REPOSITORY_H
#define I_FILE_SAVER_REPOSITORY_H

#include <QObject>
#include "../entity/proccessed_file.h"

class IFileSaverRepository : public QObject
{
    Q_OBJECT
public:
    explicit IFileSaverRepository(QObject *parent = nullptr);
    virtual void saveFiles(QString dist, QString dirName, QList<ProccessedFile> files) = 0;
signals:
};

#endif // I_FILE_SAVER_REPOSITORY_H
