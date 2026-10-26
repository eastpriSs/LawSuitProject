#ifndef LOAD_LOOKUP_LIST_H
#define LOAD_LOOKUP_LIST_H

#include <QObject>
#include "../entity/lookup_list_type.h"
#include "../repo_interfaces/i_lookup_list_repository.h"

class LoadLookupList : public QObject {
public:
    explicit LoadLookupList(ILookupListRepository* r) : repo(r) {}
    QStringList operator()(LookupListType type) const;
private:
    ILookupListRepository* repo;
};

#endif // LOAD_LOOKUP_LIST_H
