#ifndef LOAD_SUIT_H
#define LOAD_SUIT_H

#include <QObject>
#include "../entity/form_data_map.h"
#include "../repo_interfaces/i_file_reader_repository.h"
#include "../repo_interfaces/i_recovery_file_maker.h"

class LoadSuit : public QObject
{
    Q_OBJECT
public:
    LoadSuit(IFileReaderRepository* reader, IRecoveryFileMaker* s, QObject* parent = nullptr)
        : serializer(s), fileReader(reader), QObject{parent} {}
    explicit LoadSuit(QObject *parent = nullptr);
    void operator()(QString src);
signals:
    void SuitLoaded(FormDataMap data);
private:
    IFileReaderRepository* fileReader;
    IRecoveryFileMaker* serializer;
};

#endif // LOAD_SUIT_H
