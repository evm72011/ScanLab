cmake_minimum_required(VERSION 3.16)

project(ScanLab VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

SET(APP_NAME appScanLab)

qt_add_executable(${APP_NAME}
    app/main.cpp
)

qt_add_qml_module(${APP_NAME}
    URI ScanLab
    QML_FILES
        qml/Main.qml
        qml/pages/LoadPage.qml
        qml/pages/MainPage.qml
        qml/pages/ConnectPage.qml
    SOURCES
        app/include/backend.h
        app/src/backend.cpp
#        RESOURCES external/third_party/include/_read.me
)


include(GNUInstallDirs)
install(TARGETS ${APP_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

#add_subdirectory(libs)
add_subdirectory(app)
#add_subdirectory(qml)

