#ifndef PROCCESSED_FILE_H
#define PROCCESSED_FILE_H

#include <QByteArray>
#include <QString>

// todo сделать ProccessedFile_view чтобы избежать копирования m_content
// todo может стоит сделать isCreated и systemLocation, это поможет documentOpener
//      -- сразу находить файл и открывать и уменьшит привязку к пути
class ProccessedFile
{
public:
    ProccessedFile() = default;
    ProccessedFile(const QByteArray &content, const QString &fileName)
        : m_content(content), m_fileName(fileName) {}

    QByteArray content() const { return m_content; }
    QString fileName() const { return m_fileName; }

private:
    QByteArray m_content;
    QString m_fileName;
};

#endif // PROCCESSED_FILE_H
