#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include <QFile>
#include "document_opener.h"

DocumentOpener::DocumentOpener(const QString& sd)
    : systemDir(sd)
{}

void DocumentOpener::open(QList<ProccessedFile> files)
{
    foreach (ProccessedFile file , files) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(systemDir + file.fileName()));
    }
}
