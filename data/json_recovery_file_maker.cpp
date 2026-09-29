#include <QJsonDocument>
#include <QJsonObject>
#include "json_recovery_file_maker.h"

ProccessedFile JsonRecoveryFileMaker::make(const FormDataMap& formData) const
{
    const QJsonObject obj = QJsonObject::fromVariantMap(formData.raw());
    const QJsonDocument doc(obj);

    return ProccessedFile(
        doc.toJson(QJsonDocument::Indented),
        "recovery.json"
        );
}
