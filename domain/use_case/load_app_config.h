#ifndef LOAD_APP_CONFIG_H
#define LOAD_APP_CONFIG_H

#include "../repo_interfaces/i_config_repository.h"
#include "../entity/app_config.h"

class LoadAppConfig {
    IConfigRepository* repo;
public:
    LoadAppConfig(IConfigRepository* r) : repo(r) {}

    AppConfig operator()() {
        return repo->loadConfig();
    }
};

#endif // LOAD_APP_CONFIG_H
