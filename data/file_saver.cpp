#include <QDir>
#include "file_saver.h"

void FileSaver::saveFiles(QString dist, QList<ProccessedFile> files)
{
    QDir subDirDist;
    subDirDist.mkdir(dist);

    for (const ProccessedFile &file : files) {
        if (file.content().isEmpty()) {
            qWarning() << "Skipping empty file:" << file.fileName();
            continue;
        }

        QString filePath = dist + "/" + file.fileName();
        QFile f(filePath);
        if (!f.open(QIODevice::WriteOnly)) {
            qWarning() << "Cannot open file for writing:" << filePath;
            continue;
        }

        qint64 written = f.write(file.content());
        if (written != file.content().size()) {
            qWarning() << "Failed to write all bytes to" << filePath
                       << "Expected:" << file.content().size()
                       << "Written:" << written;
        }
        f.close();
    }
}
