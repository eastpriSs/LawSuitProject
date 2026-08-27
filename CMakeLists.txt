cmake_minimum_required(VERSION 3.16)

project(LawsuitProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Xml)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(QuaZip-Qt6 REQUIRED)

qt_add_executable(Lawsuit
    main.cpp
)

qt_add_qml_module(Lawsuit
    URI LawsuitProject
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        QML_FILES qml/DatePickerPopup.qml
        QML_FILES
        SOURCES view/style_manager.h view/style_manager.cpp
        SOURCES view/file_list_model.h view/file_list_model.cpp
        QML_FILES qml/CustomGroupBox.qml
        QML_FILES qml/ContactGroupBox.qml
        QML_FILES qml/ExpertiseGroupBox.qml
        QML_FILES qml/FileListView.qml
        QML_FILES qml/ActionButtons.qml
        SOURCES presenters/form_presenter.h presenters/form_presenter.cpp
        SOURCES models/form_model.h models/form_model.cpp
        SOURCES
        SOURCES domain/use_case/update_template_list.h domain/use_case/update_template_list.cpp
        SOURCES
        SOURCES domain/repo_interfaces/i_template_repository.h domain/repo_interfaces/i_template_repository.cpp
        SOURCES data/dir_template_parser.h data/dir_template_parser.cpp
        SOURCES domain/entity/path.h domain/entity/path.cpp
        SOURCES domain/use_case/update_template_fields.h domain/use_case/update_template_fields.cpp
        SOURCES domain/repo_interfaces/i_template_fields_repository.h domain/repo_interfaces/i_template_fields_repository.cpp
        SOURCES data/txt_template_fileds_parser.h data/txt_template_fileds_parser.cpp
        QML_FILES qml/PlaintiffGroupBox.qml
        QML_FILES qml/DefendantGroupBox.qml
        SOURCES view/highlight.h view/highlight.cpp
        SOURCES view/error_handler.h view/error_handler.cpp
        SOURCES domain/repo_interfaces/i_config_repository.h domain/repo_interfaces/i_config_repository.cpp
        SOURCES domain/entity/app_config.h domain/entity/app_config.cpp
        SOURCES data/json_config_reader.h data/json_config_reader.cpp
        SOURCES domain/use_case/load_app_config.h domain/use_case/load_app_config.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(Lawsuit PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Lawsuit
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(Lawsuit
    PRIVATE Qt6::Quick
            Qt6::Xml
            QuaZip::QuaZip
)
target_link_libraries(Lawsuit PRIVATE Qt6::Core)
target_link_libraries(Lawsuit PRIVATE Qt6::Core)
target_link_libraries(Lawsuit PRIVATE Qt6::Core)

include(GNUInstallDirs)
install(TARGETS Lawsuit
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
