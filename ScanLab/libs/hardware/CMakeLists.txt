set(LIB_NAME ${HARDWARE_LIB_NAME})

add_library(${LIB_NAME} STATIC src/a_scan_acquisition.cpp
#                               src/device/device.cpp

                               src/health/health_topology.cpp
                               src/health/humidity_reader.cpp
                               src/health/humidity_topology_api.cpp
                               src/health/temperature_reader.cpp
                               src/health/temperature_topology_api.cpp
                           )

if(MOCK_DEVICE)
    target_compile_definitions(${LIB_NAME} PRIVATE  MOCK_DEVICE=1)
    target_sources(${LIB_NAME} PRIVATE  src/device/device_mock.cpp)
else()
    target_sources(${LIB_NAME} PRIVATE src/device/device.cpp)
endif()

target_include_directories(${LIB_NAME}
                           PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

target_add_oempa(TARGET ${LIB_NAME})

target_set_warnings(
    TARGET
    ${LIB_NAME}
    ENABLE
    ${ENABLE_WARNINGS}
    AS_ERRORS
    ${ENABLE_WARNINGS_AS_ERRORS})

add_sanitizer_flags(TARGET ${LIB_NAME})

target_enable_lto(
    TARGET
    ${LIB_NAME}
    ENABLE
    ${ENABLE_LTO})

#add_clang_tidy(
#    TARGET
#    ${LIB_NAME}
#    ENABLE
#    ${ENABLE_CLANG_TIDY})

if(ENABLE_TESTING)
    add_subdirectory(tests)
endif()
