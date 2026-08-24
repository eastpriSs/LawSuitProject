#ifndef HIGHLIGHT_H
#define HIGHLIGHT_H

#include <QObject>
#include <QStringList>

class Highlight : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList activeFields READ activeFields NOTIFY activeFieldsChanged)

public:
    explicit Highlight(QObject *parent = nullptr);

    QStringList activeFields() const { return m_activeFields; }

public slots:
    void setActiveFields(const QStringList &fields);

signals:
    void activeFieldsChanged();

private:
    QStringList m_activeFields;
};

#endif // HIGHLIGHT_H
