#ifndef JSON_CONFIG_READER_H
#define JSON_CONFIG_READER_H

#include <QObject>
#include "../domain/repo_interfaces/i_config_repository.h"

class JsonConfigReader : public IConfigRepository
{
public:
    JsonConfigReader() = default;
    AppConfig loadConfig() override;
};

#endif // JSON_CONFIG_READER_H
