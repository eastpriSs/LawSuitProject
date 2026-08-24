#include "highlight.h"

Highlight::Highlight(QObject *parent) : QObject(parent) {}

void Highlight::setActiveFields(const QStringList &fields)
{
    if (m_activeFields != fields) {
        m_activeFields = fields;
        emit activeFieldsChanged();
    }
}
