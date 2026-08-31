#ifndef FORM_DATA_MAP_H
#define FORM_DATA_MAP_H

#include <QVariantMap>
#include <QString>

class FormDataMap
{
public:
    struct ContactInfo {
        QString name;
        QString address;
        QString phone;
        QString representative;
    };

    struct MainInfo {
        QString caseName;
        QString caseID;
        QString dateReceived;
        QString judgeName;
        QString judgePhone;
        QString courtType;
        QString courtAddress;
    };

    struct ExpertiseInfo {
        QString type;
        QString subject;
        QString expert;
        QString dueDate;
        QString travelCost;
        QString totalCost;
    };

    struct LawsuitData {
        MainInfo main;
        ContactInfo plaintiff;
        ContactInfo defendant;
        ExpertiseInfo expertise;
    };

    bool parse(const QVariantMap &formData);
    LawsuitData getData() const { return m_data; }
    QMap<QString, QString> toPlaceholderMap() const;

private:
    LawsuitData m_data;
};

#endif // FORM_DATA_MAP_H
