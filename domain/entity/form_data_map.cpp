#include "form_data_map.h"

bool FormDataMap::parse(const QVariantMap &formData)
{
    m_raw = formData;

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
    m_data.plaintiff.isPayer        = tempMap.value("isPayer").toBool();

    // --- Ответчик ---
    tempMap = formData["defendant"].toMap();
    m_data.defendant.name           = tempMap.value("name").toString();
    m_data.defendant.address        = tempMap.value("address").toString();
    m_data.defendant.phone          = tempMap.value("phone").toString();
    m_data.defendant.representative = tempMap.value("representative").toString();
    m_data.defendant.isPayer        = tempMap.value("isPayer").toBool();

    // --- Экспертиза ---
    tempMap = formData["expertise"].toMap();
    m_data.expertise.type       = tempMap.value("type").toString();
    m_data.expertise.expert     = tempMap.value("expert").toString();
    m_data.expertise.dueDate    = tempMap.value("dueDate").toString();
    m_data.expertise.travelCost = tempMap.value("travelCost").toString();
    m_data.expertise.totalCost  = tempMap.value("totalCost").toString();

    return true;
}

QMap<QString, QString> FormDataMap::toPlaceholderMap() const
{
    QMap<QString, QString> map;

    // --- Основная информация ---
    map["метка_наименование_дела"]   = m_data.main.caseName;
    map["метка_номер_дела"]          = m_data.main.caseID;
    map["метка_дата_получения_дела"] = m_data.main.dateReceived;
    map["метка_фио_судьи"]           = m_data.main.judgeName;
    map["метка_телефон_судьи"]       = m_data.main.judgePhone;
    map["метка_наименование_суда"]   = m_data.main.courtType;
    map["метка_адрес_суда"]          = m_data.main.courtAddress;

    // --- Истец ---
    map["метка_фио_истца"]           = m_data.plaintiff.name;
    map["метка_адрес_истца"]         = m_data.plaintiff.address;
    map["метка_телефон_истца"]       = m_data.plaintiff.phone;
    map["метка_представитель_истца"] = m_data.plaintiff.representative;

    // --- Ответчик ---
    map["метка_фио_ответчика"]           = m_data.defendant.name;
    map["метка_адрес_ответчика"]         = m_data.defendant.address;
    map["метка_телефон_ответчика"]       = m_data.defendant.phone;
    map["метка_представитель_ответчика"] = m_data.defendant.representative;

    // --- Экспертиза ---
    map["метка_вид_экспертизы"]     = m_data.expertise.type;
    map["метка_эксперт"]            = m_data.expertise.expert;
    map["метка_срок_исполнения"]    = m_data.expertise.dueDate;
    map["метка_стоимость_выезда"]   = m_data.expertise.travelCost;
    map["метка_итоговая_стоимость"] = m_data.expertise.totalCost;

    // --- Плательщик ---
    if (m_data.plaintiff.isPayer) {
        map["метка_плательщик"]               = m_data.plaintiff.name;
        map["метка_адрес_плательщика"]        = m_data.plaintiff.address;
        map["метка_телефон_плательщика"]      = m_data.plaintiff.phone;
        map["метка_представитель_плательщика"] = m_data.plaintiff.representative;
    } else if (m_data.defendant.isPayer) {
        map["метка_плательщик"]               = m_data.defendant.name;
        map["метка_адрес_плательщика"]        = m_data.defendant.address;
        map["метка_телефон_плательщика"]      = m_data.defendant.phone;
        map["метка_представитель_плательщика"] = m_data.defendant.representative;
    }

    return map;
}
