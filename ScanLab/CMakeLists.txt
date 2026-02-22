cmake_minimum_required(VERSION 3.16)

project(ScanLab VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

SET(APP_NAME appScanLab)
set(OEMPA_SDK_DIR "C:/ProgramData/AOS/OEMPA 1.3.0.2/Sources")
set(OEMPA_ENABLE ON)

qt_add_executable(${APP_NAME}
    app/main.cpp
)

qt_add_qml_module(${APP_NAME}
    URI ScanLab
    QML_FILES
        qml/Main.qml
        qml/components/IconTabButton.qml

        qml/pages/ConnectPage.qml
        qml/pages/LoadPage.qml
        qml/pages/MainPage.qml

    SOURCES
        app/include/backend.h
        app/src/backend.cpp
#    RESOURCES
#        resources/icons/cog.svg
)

qt_add_resources(${APP_NAME} app_resources
    PREFIX "/"
    FILES
#        resources/icons/home.svg
        resources/icons/cog.svg
        resources/icons/cogs.png
)

include(GNUInstallDirs)
install(TARGETS ${APP_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(OEMPA)

#add_subdirectory(libs)
add_subdirectory(app)
#add_subdirectory(qml)

