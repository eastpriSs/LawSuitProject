#ifndef HIGHLIGHT_H
#define HIGHLIGHT_H

#include <QObject>
#include <QSet>

class Highlight : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QSet<QString> activeFields READ activeFields NOTIFY activeFieldsChanged)

public:
    explicit Highlight(QObject *parent = nullptr);
    QSet<QString> activeFields() const { return m_activeFields; }

public slots:
    void setActiveFields(QSet<QString> fields);

signals:
    void activeFieldsChanged();

private:
    QSet<QString> m_activeFields;
};

#endif // HIGHLIGHT_H
