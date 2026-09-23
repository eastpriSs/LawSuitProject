#ifndef XML_TAGS_REPLACER_H
#define XML_TAGS_REPLACER_H

#include "../domain/repo_interfaces/i_files_proccessor_repository.h"

class XmlTagsReplacer : public IFilesProccessorRepository
{
public:
    XmlTagsReplacer() = default;
    ProccessedFile proccess(const QString& file, const FormDataMap& data) override;
};

#endif // XML_TAGS_REPLACER_H
