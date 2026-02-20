cmake_minimum_required(VERSION 3.16)

project(ScanLab VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appScanLab
    src/app/src/main.cpp
)

qt_add_qml_module(appScanLab
    URI ScanLab
    QML_FILES
        src/qml/Main.qml
        src/qml/pages/LoadPage.qml
        src/qml/pages/MainPage.qml
        src/qml/pages/ConnectPage.qml
        SOURCES src/app/include/backend.h
        SOURCES src/app/src/backend.cpp
#        RESOURCES external/third_party/include/_read.me
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appScanLab PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appScanLab
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appScanLab
    PRIVATE Qt6::Quick
)

target_include_directories(appScanLab PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/oempa/include
)

include(GNUInstallDirs)
install(TARGETS appScanLab
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
