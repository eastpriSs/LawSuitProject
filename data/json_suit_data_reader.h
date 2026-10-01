#ifndef JSON_SUIT_DATA_READER_H
#define JSON_SUIT_DATA_READER_H

#include "../domain/repo_interfaces/i_file_reader_repository.h"

class JsonSuitDataReader : public IFileReaderRepository
{
public:
    QByteArray readFile(const QString& path) const override;
    bool exists(const QString& path) const override;
};

#endif // JSON_SUIT_DATA_READER_H
