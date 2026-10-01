#ifndef I_FILE_READER_REPOSITORY_H
#define I_FILE_READER_REPOSITORY_H

#include <QObject>
#include <QByteArray>
#include <QString>

class IFileReaderRepository : public QObject
{
    Q_OBJECT
public:
    explicit IFileReaderRepository(QObject *parent = nullptr)
        : QObject{parent} {}

    virtual QByteArray readFile(const QString& path) const = 0;
    virtual bool exists(const QString& path) const = 0;
};

#endif // I_FILE_READER_REPOSITORY_H
