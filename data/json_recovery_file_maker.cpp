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

FormDataMap JsonRecoveryFileMaker::deserialize(const QByteArray &content) const
{
    QJsonParseError err{};
    const QJsonDocument doc = QJsonDocument::fromJson(content, &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject()) {
        return {};
    }

    FormDataMap fd;
    fd.parse(doc.object().toVariantMap());
    return fd;
}
