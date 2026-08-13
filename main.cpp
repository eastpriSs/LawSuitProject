#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>
#include <QFile>
#include <QDomDocument>
#include <QMap>
#include <QDebug>

#include <quazip.h>
#include <quazipfile.h>


bool replacePlaceholdersInDocx(const QString &inputPath,
                               const QString &outputPath,
                               const QMap<QString, QString> &placeholders)
{
    const QString WORDML_NS = "http://schemas.openxmlformats.org/wordprocessingml/2006/main";

    // --- Чтение исходного docx как ZIP ---
    QuaZip zipIn(inputPath);
    if (!zipIn.open(QuaZip::mdUnzip)) {
        qWarning() << "Failed to open input docx:" << inputPath;
        return false;
    }

    // Извлекаем word/document.xml
    QByteArray documentXml;
    {
        QuaZipFile fileIn(&zipIn);
        if (!zipIn.setCurrentFile("word/document.xml") ||
            !fileIn.open(QIODevice::ReadOnly)) {
            qWarning() << "word/document.xml not found in archive";
            zipIn.close();
            return false;
        }
        documentXml = fileIn.readAll();
        fileIn.close();
    }
    zipIn.close();

    // --- Парсинг и замена ---
    QDomDocument doc;

    doc.setContent(documentXml, QDomDocument::ParseOption::UseNamespaceProcessing);

    QDomNodeList tNodes = doc.elementsByTagNameNS(WORDML_NS, "t");
    for (int i = 0; i < tNodes.count(); ++i) {
        QDomElement tElem = tNodes.at(i).toElement();
        QString text = tElem.text();

        bool changed = false;
        for (auto it = placeholders.cbegin(); it != placeholders.cend(); ++it) {
            const QString placeholder = QStringLiteral("{{%1}}").arg(it.key());
            if (text.contains(placeholder)) {
                text.replace(placeholder, it.value());
                changed = true;
            }
        }

        if (changed) {
            // Удаляем старое содержимое и вставляем новый текст
            while (tElem.hasChildNodes())
                tElem.removeChild(tElem.firstChild());
            tElem.appendChild(doc.createTextNode(text));
        }
    }

    // --- Запись в новый docx (копируем архив, заменяя document.xml) ---
    QuaZip zipOut(outputPath);
    if (!zipOut.open(QuaZip::mdCreate)) {
        qWarning() << "Failed to create output docx:" << outputPath;
        return false;
    }

    // Переоткрываем исходный архив для копирования
    QuaZip zipIn2(inputPath);
    if (!zipIn2.open(QuaZip::mdUnzip)) {
        qWarning() << "Failed to reopen input docx";
        zipOut.close();
        return false;
    }

    QuaZipFile srcFile(&zipIn2);
    QuaZipFile dstFile(&zipOut);

    const QStringList fileNames = zipIn2.getFileNameList();
    for (const QString &fileName : fileNames) {
        if (!zipIn2.setCurrentFile(fileName)) continue;
        if (!srcFile.open(QIODevice::ReadOnly)) continue;

        QuaZipNewInfo newInfo(fileName);
        if (fileName == "word/document.xml") {
            // Подставляем модифицированный XML
            const QByteArray newXml = doc.toByteArray();
            newInfo.uncompressedSize = newXml.size();
            if (!dstFile.open(QIODevice::WriteOnly, newInfo)) return false;
            dstFile.write(newXml);
            dstFile.close();
        } else {
            // Остальные файлы копируем как есть
            if (!dstFile.open(QIODevice::WriteOnly, newInfo)) return false;
            dstFile.write(srcFile.readAll());
            dstFile.close();
        }
        srcFile.close();
    }

    zipIn2.close();
    zipOut.close();
    return true;
}


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/LawsuitProject/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
