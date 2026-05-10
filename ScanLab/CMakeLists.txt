cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(QT_CREATOR_SKIP_CONAN_SETUP
    ON
    CACHE BOOL "" FORCE)

project(
    ScanLab
    VERSION 0.1.0
    LANGUAGES CXX)

add_compile_definitions(NOMINMAX WIN32_LEAN_AND_MEAN)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)
find_package(magic_enum REQUIRED)

qt_standard_project_setup(REQUIRES 6.8)

set(VENV_DIR
    "${CMAKE_SOURCE_DIR}/.venv"
    CACHE PATH "Path to Python virtual environment")

set(CORE_LIB_NAME "scanlab-core")
set(LICENSE_LIB_NAME "scanlab-license")
set(APP_NAME appScanLab)

set(OEMPA_SDK_DIR "C:/ProgramData/AOS/OEMPA 1.3.0.2/Sources")
set(OEMPA_ENABLE ON)

unset(MOCK_DEVICE CACHE)
option(MOCK_DEVICE "Use mock hardware implementation" ON)

set(SCANLAB_LICENSE_FILE "license.json")
set(SCANLAB_LICENSE_PUBLIC_KEY "au1UA+apb0TTkDj8GDU+yq+dQvkfkM59hqrXlE01818=")

option(ENABLE_WARNINGS "Enable to add warnings to a target." ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable compiler warnings as errors" OFF)

option(ENABLE_LTO "Enable to add Link Time Optimization." OFF)

option(ENABLE_SANITIZE_ADDR "Enable address sanitize." OFF)
option(ENABLE_SANITIZE_UNDEF "Enable undefined sanitize." OFF)
option(ENABLE_SANITIZE_LEAK "Enable leak sanitize (Gcc/Clang only)." OFF)
option(ENABLE_SANITIZE_THREAD "Enable thread sanitize (Gcc/Clang only)." OFF)

option(ENABLE_TESTING "Enable testing." OFF)

option(ENABLE_CLANG_TIDY "Enable to add clang tidy." ON)
option(ENABLE_CLANG_FORMAT "Enable to add clang-format." ON)
option(ENABLE_CMAKE_FORMAT "Enable to add cmake-format." ON)

qt_add_executable(${APP_NAME} app/main.cpp)

qt_add_qml_module(
    ${APP_NAME}
    URI
    ScanLab
    VERSION
    1.0
    SOURCES
    app/include/runtime/acquisition/acquisition_configuration_service.h
    app/include/runtime/acquisition/acquisition_configuration_worker.h
    app/include/runtime/acquisition/ascan/ascan_service.h
    app/include/runtime/acquisition/ascan/ascan_worker.h
    app/include/runtime/config/config_callback_service.h
    app/include/runtime/config/config_callback_worker.h
    app/include/runtime/config/config_file_service.h
    app/include/runtime/config/config_file_worker.h
    app/include/runtime/device/device_context.h
    app/include/runtime/device/device_type.h
    app/include/runtime/device/device_type_def.h
    app/include/runtime/device/device_type_mapper.h
    app/include/runtime/errors/error_info.h
    app/include/runtime/errors/describe_error.h
    app/include/runtime/errors/describe_error_hw.h
    app/include/runtime/connection/connection_error.h
    app/include/runtime/connection/connection_service.h
    app/include/runtime/connection/connection_worker.h
    app/include/runtime/health/humidity_service.h
    app/include/runtime/health/humidity_worker.h
    app/include/runtime/health/temperature_service.h
    app/include/runtime/health/temperature_worker.h
    app/include/runtime/shell/shell_services.h
    app/include/runtime/shell/toast/toast_service.h
    #
    app/include/ui/app_info.h
    app/include/ui/acquisition/acquisition_configuration_facade.h
    app/include/ui/acquisition/ascan_facade.h
    app/include/ui/config/config_callback_facade.h
    app/include/ui/config/config_file_facade.h
    app/include/ui/connection/connection_facade.h
    app/include/ui/connection/connection_state.h
    app/include/ui/device/device_type.h
    app/include/ui/health/temperature_facade.h
    app/include/ui/health/humidity_facade.h
    app/include/ui/shell/shell_facade.h
    app/include/ui/shell/toast/toast_facade.h
    app/include/ui/view/ascan_view.h
    #
    app/include/app_settings.h
    app/include/backend.h
    #
    app/include/b_scan_view.h
    app/include/b_scan_worker.h
    app/include/c_scan_view.h
    app/include/c_scan_worker.h
    #-----------
    app/src/runtime/acquisition/acquisition_configuration_service.cpp
    app/src/runtime/acquisition/acquisition_configuration_worker.cpp
    app/src/runtime/acquisition/ascan/ascan_service.cpp
    app/src/runtime/acquisition/ascan/ascan_worker.cpp
    app/src/runtime/config/config_callback_service.cpp
    app/src/runtime/config/config_callback_worker.cpp
    app/src/runtime/config/config_file_service.cpp
    app/src/runtime/config/config_file_worker.cpp
    app/src/runtime/device/device_context.cpp
    app/src/runtime/connection/connection_service.cpp
    app/src/runtime/connection/connection_worker.cpp
    app/src/runtime/health/humidity_service.cpp
    app/src/runtime/health/humidity_worker.cpp
    app/src/runtime/health/temperature_service.cpp
    app/src/runtime/health/temperature_worker.cpp
    app/src/runtime/shell/shell_services.cpp
    app/src/runtime/shell/toast/toast_service.cpp
    #
    app/src/ui/acquisition/acquisition_configuration_facade.cpp
    app/src/ui/acquisition/ascan_facade.cpp
    app/src/ui/config/config_callback_facade.cpp
    app/src/ui/config/config_file_facade.cpp
    app/src/ui/connection/connection_facade.cpp
    app/src/ui/health/temperature_facade.cpp
    app/src/ui/health/humidity_facade.cpp
    app/src/ui/shell/shell_facade.cpp
    app/src/ui/shell/toast/toast_facade.cpp
    app/src/ui/view/ascan_view.cpp
    #
    app/src/backend.cpp
    #
    app/src/b_scan_view.cpp
    app/src/b_scan_worker.cpp
    app/src/c_scan_view.cpp
    app/src/c_scan_worker.cpp)

include(GNUInstallDirs)
install(
    TARGETS ${APP_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(License)
include(OEMPA)
include(OEMPA_config)
include(Warnings)
include(LTO)
include(Sanitizer)

include(ClangTidy)
include(ClangFormat)
include(CMakeFormat)
add_clang_format_target()
add_cmake_format_target()

add_subdirectory(resources)
add_subdirectory(libs)
add_subdirectory(qml)
add_subdirectory(app)
