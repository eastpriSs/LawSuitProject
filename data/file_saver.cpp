#include <QDir>
#include "file_saver.h"

void FileSaver::saveFiles(QString dist, QString dirName, QList<ProccessedFile> files)
{
    QString testPath = dist + "/" + dirName;
    QDir().mkpath(testPath);

    for (const ProccessedFile &file : files) {
        if (file.content().isEmpty()) {
            qWarning() << "Skipping empty file:" << file.fileName();
            continue;
        }

        QString filePath = testPath + "/" + file.fileName();
        qInfo() << filePath;
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
