#ifndef SAVE_LOOKUP_LIST_H
#define SAVE_LOOKUP_LIST_H

#include "../entity/lookup_list_type.h"
#include "../repo_interfaces/i_lookup_list_repository.h"

class SaveLookupList {
public:
    explicit SaveLookupList(ILookupListRepository* r) : repo(r) {}
    bool operator()(LookupListType type, const QStringList& items) {
        return repo->save(type, items);
    }
private:
    ILookupListRepository* repo;
};

#endif // SAVE_LOOKUP_LIST_H
