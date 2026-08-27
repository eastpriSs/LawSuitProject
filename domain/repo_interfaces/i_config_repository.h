#ifndef I_CONFIG_REPOSITORY_H
#define I_CONFIG_REPOSITORY_H

#include "../entity/app_config.h"

class IConfigRepository {
public:
    virtual ~IConfigRepository() = default;
    virtual AppConfig loadConfig() = 0;
};

#endif // I_CONFIG_REPOSITORY_H
