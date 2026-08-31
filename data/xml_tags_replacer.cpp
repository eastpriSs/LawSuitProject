#include "xml_tags_replacer.h"
#include <QDomDocument>
#include <QBuffer>
#include <QDebug>
#include <quazip.h>
#include <quazipfile.h>

static QByteArray replaceInDocx(const QString &_templatePath, const QMap<QString, QString> &placeholders)
{
    const QString WORDML_NS = "http://schemas.openxmlformats.org/wordprocessingml/2006/main";

    QString templatePath = "templates/" + _templatePath; // todo

    QuaZip zipIn(templatePath);
    if (!zipIn.open(QuaZip::mdUnzip)) {
        qWarning() << "Failed to open template docx:" << templatePath;
        return QByteArray();
    }

    QByteArray documentXml;
    {
        QuaZipFile fileIn(&zipIn);
        if (!zipIn.setCurrentFile("word/document.xml") || !fileIn.open(QIODevice::ReadOnly)) {
            qWarning() << "word/document.xml not found in archive";
            zipIn.close();
            return QByteArray();
        }
        documentXml = fileIn.readAll();
        fileIn.close();
    }
    zipIn.close();

    // 2. Разобрать XML
    QDomDocument doc;
    QString errorMsg;
    int errorLine, errorCol;
    if (!doc.setContent(documentXml, QDomDocument::ParseOption::UseNamespaceProcessing)) {
        qWarning() << "Failed to parse document.xml:" << errorMsg << "at" << errorLine << errorCol;
        return QByteArray();
    }

    // 3. Заменить плейсхолдеры вида {{key}} во всех текстовых узлах
    QDomNodeList tNodes = doc.elementsByTagNameNS(WORDML_NS, "t");
    qInfo() << tNodes.count();
    for (int i = 0; i < tNodes.count(); ++i) {
        QDomElement tElem = tNodes.at(i).toElement();
        QString text = tElem.text();
        qInfo() << text;
        bool changed = false;
        for (auto it = placeholders.cbegin(); it != placeholders.cend(); ++it) {
            const QString placeholder = QStringLiteral("{{%1}}").arg(it.key());
            if (text.contains(placeholder)) {
                text.replace(placeholder, it.value());
                changed = true;
            }
        }
        if (changed) {
            while (tElem.hasChildNodes())
                tElem.removeChild(tElem.firstChild());
            tElem.appendChild(doc.createTextNode(text));
        }
    }

    // 4. Создать новый ZIP в памяти с обновлённым document.xml
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    QuaZip zipOut(&buffer);
    if (!zipOut.open(QuaZip::mdCreate)) {
        qWarning() << "Failed to create in-memory zip";
        return QByteArray();
    }

    // Копируем все файлы из исходного шаблона, заменяя word/document.xml
    QuaZip zipIn2(templatePath);
    if (!zipIn2.open(QuaZip::mdUnzip)) {
        qWarning() << "Failed to reopen template for copying";
        zipOut.close();
        return QByteArray();
    }

    QuaZipFile srcFile(&zipIn2);
    QuaZipFile dstFile(&zipOut);

    const QStringList fileNames = zipIn2.getFileNameList();
    for (const QString &fileName : fileNames) {
        if (!zipIn2.setCurrentFile(fileName)) continue;
        if (!srcFile.open(QIODevice::ReadOnly)) continue;

        QuaZipNewInfo newInfo(fileName);
        if (fileName == "word/document.xml") {
            const QByteArray newXml = doc.toByteArray();
            newInfo.uncompressedSize = newXml.size();
            if (!dstFile.open(QIODevice::WriteOnly, newInfo)) {
                zipOut.close();
                return QByteArray();
            }
            dstFile.write(newXml);
            dstFile.close();
        } else {
            if (!dstFile.open(QIODevice::WriteOnly, newInfo)) {
                zipOut.close();
                return QByteArray();
            }
            dstFile.write(srcFile.readAll());
            dstFile.close();
        }
        srcFile.close();
    }

    zipIn2.close();
    zipOut.close();
    buffer.close();

    return buffer.data();
}

ProccessedFile XmlTagsReplacer::proccess(const QString &file, const FormDataMap &data)
{
    QByteArray processedContent = replaceInDocx(file, data.toPlaceholderMap());
    return ProccessedFile{processedContent, file};
}
