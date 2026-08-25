#include "error_handler.h"
#include <QDebug>

ErrorHandler::ErrorHandler(QObject *parent) : QObject(parent) {}

void ErrorHandler::handleError(const QString &title, const QString &message)
{
    emit statusMessageChanged(QString("%1: %2").arg(title, message));
    emit showErrorDialog(title, message);
}

void ErrorHandler::setAppState(QString state)
{
    if (m_appState != state){
        m_appState = state;
        emit appStateChanged();
    }
}
