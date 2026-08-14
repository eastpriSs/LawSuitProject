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

    QuaZip zipIn(inputPath);
    if (!zipIn.open(QuaZip::mdUnzip)) {
        qWarning() << "Failed to open input docx:" << inputPath;
        return false;
    }

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
            while (tElem.hasChildNodes())
                tElem.removeChild(tElem.firstChild());
            tElem.appendChild(doc.createTextNode(text));
        }
    }

    QuaZip zipOut(outputPath);
    if (!zipOut.open(QuaZip::mdCreate)) {
        qWarning() << "Failed to create output docx:" << outputPath;
        return false;
    }

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
            const QByteArray newXml = doc.toByteArray();
            newInfo.uncompressedSize = newXml.size();
            if (!dstFile.open(QIODevice::WriteOnly, newInfo)) return false;
            dstFile.write(newXml);
            dstFile.close();
        } else {
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


// int main(int argc, char *argv[])
// {
//     QGuiApplication app(argc, argv);

//     QQmlApplicationEngine engine;
//     const QUrl url(QStringLiteral("qrc:/LawsuitProject/Main.qml"));
//     QObject::connect(
//         &engine,
//         &QQmlApplicationEngine::objectCreated,
//         &app,
//         [url](QObject *obj, const QUrl &objUrl) {
//             if (!obj && url == objUrl)
//                 QCoreApplication::exit(-1);
//         },
//         Qt::QueuedConnection);
//     engine.load(url);

//     return app.exec();
// }


#include <QQmlContext>
#include "view/style_manager.h"
#include "view/file_list_model.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    StyleManager styleManager;
    FileListModel fileModel;

    fileModel.appendItem("Bill Smith", "555 3264", false);
    fileModel.appendItem("John Brown", "555 8426", false);
    fileModel.appendItem("Sam Wise", "555 0473", false);

    engine.rootContext()->setContextProperty("StyleManager", &styleManager);
    engine.rootContext()->setContextProperty("FileModel", &fileModel);

    engine.load(QUrl(QStringLiteral("qrc:/LawsuitProject/qml/Main.qml")));

    return app.exec();
}
