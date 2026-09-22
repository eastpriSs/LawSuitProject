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

#include "view/style_manager.h"
#include "view/file_list_model.h"
#include "presenters/form_presenter.h"
#include "models/form_model.h"
#include "domain/use_case/update_template_list.h"
#include "domain/use_case/update_template_fields.h"
#include "domain/use_case/save_files.h"
#include "data/dir_template_parser.h"
#include "data/txt_template_fileds_parser.h"
#include "data/xml_tags_replacer.h"
#include "data/file_saver.h"
#include "view/highlight.h"
#include "view/error_handler.h"


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

    DirTemplateParser dirParser;
    TemplateFieldsTxtParser txtParser;
    XmlTagsReplacer replacer;
    FileSaver fs;

    SaveFiles saveFiles(&fs, &replacer);
    UpdateTemplateList updateTemplates(&dirParser);
    UpdateTemplateFields updateTemplatesFields(&txtParser);
    FormModel model(&updateTemplates, &updateTemplatesFields, &saveFiles);
    FormPresenter presenter(&fileModel, &model, &highlight, &errorHandler);

    engine.rootContext()->setContextProperty("Presenter", &presenter);
    engine.load(QUrl(QStringLiteral("qrc:/LawsuitProject/qml/Main.qml")));

    return app.exec();
}
