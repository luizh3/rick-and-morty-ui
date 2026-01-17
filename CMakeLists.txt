cmake_minimum_required(VERSION 3.16)

project(rick-and-morty-ui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Network REQUIRED)

qt_add_executable(apprick-and-morty-ui
    main.cpp
)

qt_add_qml_module(apprick-and-morty-ui
    URI rick-and-morty-ui
    VERSION 1.0
    QML_FILES main.qml
    QML_FILES ui/EpisodeScreen.qml
    QML_FILES ui/EpisodeScreenDesign.ui.qml
    SOURCES control/episodescreencontrol.h control/episodescreencontrol.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apprick-and-morty-ui PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apprick-and-morty-ui
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apprick-and-morty-ui
    PRIVATE
    core
    Qt6::Quick
    Qt6::Network
)

include(GNUInstallDirs)
install(TARGETS apprick-and-morty-ui
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

add_subdirectory(core)
