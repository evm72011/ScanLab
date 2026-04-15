find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2 Svg)

set_target_properties(${APP_NAME} PROPERTIES
    OUTPUT_NAME ScanLab
)

target_include_directories(${APP_NAME} PRIVATE
    include
    include/ui/connection
    include/ui/device
    include/ui/health
    ${CMAKE_BINARY_DIR}/configured/include
)

target_link_libraries(${APP_NAME}
    PRIVATE Qt6::Quick ${HARDWARE_LIB_NAME}
)

set_target_properties(${APP_NAME} PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appScanLab
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

add_subdirectory(config)

target_add_oempa(TARGET ${APP_NAME})
