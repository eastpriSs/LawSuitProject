#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>
#include <QFile>
#include <QDomDocument>
#include <QMap>
#include <QDebug>
#include <QQmlContext>
#include <quazip.h>
#include <quazipfile.h>

// View
#include "view/style_manager.h"
#include "view/file_list_model.h"
#include "view/highlight.h"
#include "view/error_handler.h"

// Presenters & Models
#include "presenters/form_presenter.h"
#include "models/form_model.h"

// Domain (Use Cases & Entities)
#include "domain/entity/app_config.h"
#include "domain/use_case/load_app_config.h"
#include "domain/use_case/update_template_list.h"
#include "domain/use_case/update_template_fields.h"

// Data (Repositories / Parsers)
#include "data/json_config_reader.h" // Или json_config_repository.h, в зависимости от вашего имени
#include "data/dir_template_parser.h"
#include "data/txt_template_fileds_parser.h"

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

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    StyleManager styleManager;
    FileListModel fileModel;
    Highlight highlight;
    ErrorHandler errorHandler;

    engine.rootContext()->setContextProperty("errorHandler", &errorHandler);
    engine.rootContext()->setContextProperty("Highlight", &highlight);
    engine.rootContext()->setContextProperty("StyleManager", &styleManager);
    engine.rootContext()->setContextProperty("FileModel", &fileModel);

    engine.load(QUrl(QStringLiteral("qrc:/LawsuitProject/qml/Main.qml")));

    JsonConfigReader configRepo;
    LoadAppConfig loadConfigUseCase(&configRepo);
    AppConfig appConfig = loadConfigUseCase();

    qInfo() << "Загружены пути из конфига:"
            << "\nШаблоны:" << appConfig.templatesPath
            << "\nПоля:" << appConfig.fieldsPath;

    DirTemplateParser dirParser(appConfig.templatesPath);
    TemplateFieldsTxtParser txtParser(appConfig.fieldsPath);

    UpdateTemplateList updateTemplates(&dirParser);
    UpdateTemplateFields updateTemplatesFields(&txtParser);

    FormModel model(&updateTemplates, &updateTemplatesFields);
    FormPresenter presenter(&fileModel, &model, &highlight, &errorHandler);

    return app.exec();
}
