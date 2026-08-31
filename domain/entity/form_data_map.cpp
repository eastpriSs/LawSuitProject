#include "form_data_map.h"

bool FormDataMap::parse(const QVariantMap &formData)
{
    if (!formData.contains("main") || !formData.contains("plaintiff") ||
        !formData.contains("defendant") || !formData.contains("expertise")) {
        return false;
    }

    // --- Основная информация ---
    QVariantMap mainMap = formData["main"].toMap();
    m_data.main.caseName       = mainMap.value("caseName").toString();
    m_data.main.caseID         = mainMap.value("caseID").toString();
    m_data.main.dateReceived   = mainMap.value("dateReceived").toString();
    m_data.main.judgeName      = mainMap.value("judgeName").toString();
    m_data.main.judgePhone     = mainMap.value("judgePhone").toString();
    m_data.main.courtType      = mainMap.value("courtType").toString();
    m_data.main.courtAddress   = mainMap.value("courtAddress").toString();

    // --- Истец ---
    QVariantMap plaintiffMap = formData["plaintiff"].toMap();
    m_data.plaintiff.name           = plaintiffMap.value("name").toString();
    m_data.plaintiff.address        = plaintiffMap.value("address").toString();
    m_data.plaintiff.phone          = plaintiffMap.value("phone").toString();
    m_data.plaintiff.representative = plaintiffMap.value("representative").toString();

    // --- Ответчик ---
    QVariantMap defendantMap = formData["defendant"].toMap();
    m_data.defendant.name           = defendantMap.value("name").toString();
    m_data.defendant.address        = defendantMap.value("address").toString();
    m_data.defendant.phone          = defendantMap.value("phone").toString();
    m_data.defendant.representative = defendantMap.value("representative").toString();

    // --- Экспертиза ---
    QVariantMap expertiseMap = formData["expertise"].toMap();
    m_data.expertise.type       = expertiseMap.value("type").toString();
    m_data.expertise.subject    = expertiseMap.value("subject").toString();
    m_data.expertise.expert     = expertiseMap.value("expert").toString();
    m_data.expertise.dueDate    = expertiseMap.value("dueDate").toString();
    m_data.expertise.travelCost = expertiseMap.value("travelCost").toString();
    m_data.expertise.totalCost  = expertiseMap.value("totalCost").toString();

    return true;
}

QMap<QString, QString> FormDataMap::toPlaceholderMap() const
{
    QMap<QString, QString> map;
    // Основная информация
    map["caseName"] = m_data.main.caseName;
    map["caseID"] = m_data.main.caseID;
    map["dateReceived"] = m_data.main.dateReceived;
    map["judgeName"] = m_data.main.judgeName;
    map["judgePhone"] = m_data.main.judgePhone;
    map["courtType"] = m_data.main.courtType;
    map["courtAddress"] = m_data.main.courtAddress;
    // Истец
    map["plaintiffName"] = m_data.plaintiff.name;
    map["plaintiffAddress"] = m_data.plaintiff.address;
    map["plaintiffPhone"] = m_data.plaintiff.phone;
    map["plaintiffRepresentative"] = m_data.plaintiff.representative;
    // Ответчик
    map["defendantName"] = m_data.defendant.name;
    map["defendantAddress"] = m_data.defendant.address;
    map["defendantPhone"] = m_data.defendant.phone;
    map["defendantRepresentative"] = m_data.defendant.representative;
    // Экспертиза
    map["expertiseType"] = m_data.expertise.type;
    map["expertiseSubject"] = m_data.expertise.subject;
    map["expert"] = m_data.expertise.expert;
    map["expertiseDueDate"] = m_data.expertise.dueDate;
    map["travelCost"] = m_data.expertise.travelCost;
    map["totalCost"] = m_data.expertise.totalCost;
    return map;
}
