#ifndef I_LOOKUP_LIST_REPOSITORY_H
#define I_LOOKUP_LIST_REPOSITORY_H

#include <QStringList>
#include "../entity/lookup_list_type.h"

class ILookupListRepository {
public:
    virtual ~ILookupListRepository() = default;
    virtual QStringList load(LookupListType type) const = 0;
    virtual bool save(LookupListType type, const QStringList& items) = 0;
};

#endif // I_LOOKUP_LIST_REPOSITORY_H
