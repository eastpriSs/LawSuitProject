#ifndef I_RECOVERY_FILE_MAKER_H
#define I_RECOVERY_FILE_MAKER_H

#include <QObject>
#include "../entity/proccessed_file.h"
#include "../entity/form_data_map.h"

class IRecoveryFileMaker : public QObject
{
    Q_OBJECT
public:
    explicit IRecoveryFileMaker(QObject *parent = nullptr)
        : QObject{parent} {}

    virtual ProccessedFile make(const FormDataMap& formData) const = 0; // serialize
    virtual FormDataMap deserialize(const QByteArray& content) const = 0;

};

#endif // I_RECOVERY_FILE_MAKER_H
