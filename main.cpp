#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

// View
#include "view/style_manager.h"
#include "view/file_list_model.h"
#include "view/highlight.h"
#include "view/error_handler.h"

// Presenters & Models
#include "presenters/form_presenter.h"
#include "models/form_model.h"

// Domain
#include "domain/use_case/update_template_list.h"
#include "domain/use_case/update_template_fields.h"
#include "domain/use_case/save_files.h"
#include "domain/entity/app_config.h"
#include "domain/use_case/load_app_config.h"
#include "domain/use_case/update_template_list.h"
#include "domain/use_case/update_template_fields.h"

// Data
#include "data/dir_template_parser.h"
#include "data/txt_template_fileds_parser.h"
#include "data/xml_tags_replacer.h"
#include "data/file_saver.h"
#include "data/json_config_reader.h"
#include "data/dir_template_parser.h"
#include "data/txt_template_fileds_parser.h"
#include "data/json_recovery_file_maker.h"
#include "data/json_suit_data_reader.h"
#include "data/json_recovery_file_maker.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    StyleManager styleManager;
    FileListModel fileModel;
    Highlight highlight;
    ErrorHandler errorHandler;
    JsonSuitDataReader reader;
    JsonRecoveryFileMaker recMaker;
    JsonConfigReader configRepo;
    LoadAppConfig loadConfigUseCase(&configRepo);
    AppConfig appConfig = loadConfigUseCase();

    qInfo() << "Загружены пути из конфига:"
            << "\nШаблоны:" << appConfig.templatesPath
            << "\nПоля:" << appConfig.fieldsPath;

    DirTemplateParser dirParser(appConfig.templatesPath);
    TemplateFieldsTxtParser txtParser(appConfig.fieldsPath);
    XmlTagsReplacer replacer;
    FileSaver fs;
    JsonRecoveryFileMaker jsonRecoveryMaker; // todo in constructor add QString filename

    QString appLoc = app.applicationFilePath();
    appLoc.erase(appLoc.begin() + appLoc.lastIndexOf("/"), appLoc.end());
    qInfo() << "Root dir of app location:" << appLoc;

    SaveFiles saveFiles(&fs, &replacer, &jsonRecoveryMaker);
    LoadSuit loadSuit(&reader, &recMaker);
    UpdateTemplateList updateTemplates(&dirParser);
    UpdateTemplateFields updateTemplatesFields(&txtParser);
    FormModel model(&updateTemplates, &updateTemplatesFields, &saveFiles, &loadSuit);
    FormPresenter presenter(&fileModel, &model, &highlight, &errorHandler);

    engine.rootContext()->setContextProperty("errorHandler", &errorHandler);
    engine.rootContext()->setContextProperty("Highlight", &highlight);
    engine.rootContext()->setContextProperty("StyleManager", &styleManager);
    engine.rootContext()->setContextProperty("FileModel", &fileModel);
    engine.rootContext()->setContextProperty("Presenter", &presenter);

    engine.load(QUrl(QStringLiteral("qrc:/LawsuitProject/qml/Main.qml")));
    return app.exec();
}
