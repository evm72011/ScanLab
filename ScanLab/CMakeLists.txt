cmake_minimum_required(VERSION 3.16)

set(QT_CREATOR_SKIP_CONAN_SETUP ON CACHE BOOL "" FORCE)

project(ScanLab VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)
find_package(magic_enum REQUIRED)

qt_standard_project_setup(REQUIRES 6.8)

set(HARDWARE_LIB_NAME "sl-hardware")
set(APP_NAME appScanLab)

set(OEMPA_SDK_DIR "C:/ProgramData/AOS/OEMPA 1.3.0.2/Sources")
set(OEMPA_ENABLE ON)

option(ENABLE_WARNINGS "Enable to add warnings to a target." ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable compiler warnings as errors" OFF)

option(ENABLE_LTO "Enable to add Link Time Optimization." OFF)

option(ENABLE_SANITIZE_ADDR "Enable address sanitize." OFF)
option(ENABLE_SANITIZE_UNDEF "Enable undefined sanitize." OFF)
option(ENABLE_SANITIZE_LEAK "Enable leak sanitize (Gcc/Clang only)." OFF)
option(ENABLE_SANITIZE_THREAD "Enable thread sanitize (Gcc/Clang only)." OFF)

#include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

qt_add_executable(${APP_NAME}
    app/main.cpp
)

target_link_libraries(${APP_NAME}
    PRIVATE
        Qt6::Quick
        Qt6::QuickControls2
        magic_enum::magic_enum
)

qt_add_qml_module(${APP_NAME}
    URI ScanLab
    VERSION 1.0
    SOURCES
        app/include/app_settings.h
        app/include/backend.h
        app/include/device_type.h
        app/include/device.h
        app/include/device_worker.h

        app/src/backend.cpp
        app/src/device.cpp
)

include(GNUInstallDirs)
install(TARGETS ${APP_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(OEMPA)
include(Warnings)
include(LTO)
include(Sanitizer)

add_subdirectory(resources)
add_subdirectory(libs)
add_subdirectory(qml)
add_subdirectory(app)
