#include "form_data_map.h"

bool FormDataMap::parse(const QVariantMap &formData)
{
    if (!formData.contains("main") || !formData.contains("plaintiff") ||
        !formData.contains("defendant") || !formData.contains("expertise")) {
        return false;
    }

    // --- Основная информация ---
    QVariantMap tempMap = formData["main"].toMap();
    m_data.main.caseName       = tempMap.value("caseName").toString();
    m_data.main.caseID         = tempMap.value("caseID").toString();
    m_data.main.dateReceived   = tempMap.value("dateReceived").toString();
    m_data.main.judgeName      = tempMap.value("judgeName").toString();
    m_data.main.judgePhone     = tempMap.value("judgePhone").toString();
    m_data.main.courtType      = tempMap.value("courtType").toString();
    m_data.main.courtAddress   = tempMap.value("courtAddress").toString();

    // --- Истец ---
    tempMap = formData["plaintiff"].toMap();
    m_data.plaintiff.name           = tempMap.value("name").toString();
    m_data.plaintiff.address        = tempMap.value("address").toString();
    m_data.plaintiff.phone          = tempMap.value("phone").toString();
    m_data.plaintiff.representative = tempMap.value("representative").toString();

    // --- Ответчик ---
    tempMap = formData["defendant"].toMap();
    m_data.defendant.name           = tempMap.value("name").toString();
    m_data.defendant.address        = tempMap.value("address").toString();
    m_data.defendant.phone          = tempMap.value("phone").toString();
    m_data.defendant.representative = tempMap.value("representative").toString();

    // --- Экспертиза ---
    tempMap = formData["expertise"].toMap();
    m_data.expertise.type       = tempMap.value("type").toString();
    m_data.expertise.subject    = tempMap.value("subject").toString();
    m_data.expertise.expert     = tempMap.value("expert").toString();
    m_data.expertise.dueDate    = tempMap.value("dueDate").toString();
    m_data.expertise.travelCost = tempMap.value("travelCost").toString();
    m_data.expertise.totalCost  = tempMap.value("totalCost").toString();

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
