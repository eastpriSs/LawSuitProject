#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <QObject>

class ErrorHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString appState READ appState NOTIFY appStateChanged)

public:
    explicit ErrorHandler(QObject *parent = nullptr);
    QString appState() const { return m_appState; }

public slots:
    void handleError(const QString &title, const QString &message);

public slots:
    void setAppState(QString state);

signals:
    void statusMessageChanged(const QString &message);
    void showErrorDialog(const QString &title, const QString &message);
    void appStateChanged();

private:
    QString m_appState;
};

#endif // ERROR_HANDLER_H
