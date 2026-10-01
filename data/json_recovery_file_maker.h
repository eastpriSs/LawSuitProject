#ifndef JSON_RECOVERY_FILE_MAKER_H
#define JSON_RECOVERY_FILE_MAKER_H

#include "../domain/repo_interfaces/i_recovery_file_maker.h"

class JsonRecoveryFileMaker : public IRecoveryFileMaker
{
public:
    using IRecoveryFileMaker::IRecoveryFileMaker;

    ProccessedFile make(const FormDataMap& formData) const override;
    FormDataMap deserialize(const QByteArray& content) const override;
};

#endif // JSON_RECOVERY_FILE_MAKER_H
