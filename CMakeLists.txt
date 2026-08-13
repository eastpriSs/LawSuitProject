cmake_minimum_required(VERSION 3.16)

project(LawsuitProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Xml)
find_package(QuaZip-Qt6 REQUIRED)

qt_add_executable(Lawsuit
    main.cpp
)

qt_add_qml_module(Lawsuit
    URI LawsuitProject
    VERSION 1.0
    QML_FILES
        Main.qml
        QML_FILES DatePickerPopup.qml
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

include(GNUInstallDirs)
install(TARGETS Lawsuit
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
