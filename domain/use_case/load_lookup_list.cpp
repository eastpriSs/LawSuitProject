#include "load_lookup_list.h"


QStringList LoadLookupList::operator()(LookupListType type) const
{
    return repo->load(type);
}
