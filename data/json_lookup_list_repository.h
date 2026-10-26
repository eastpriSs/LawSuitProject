#ifndef JSON_LOOKUP_LIST_REPOSITORY_H
#define JSON_LOOKUP_LIST_REPOSITORY_H

#include "../domain/repo_interfaces/i_lookup_list_repository.h"

class JsonLookupListRepository : public ILookupListRepository
{
public:
    JsonLookupListRepository(const QString& cfgf);

    QStringList load(LookupListType type) const override;
    bool save(LookupListType type, const QStringList& items) override;
private:
    QString cfgFile;
};

#endif // JSON_LOOKUP_LIST_REPOSITORY_H
