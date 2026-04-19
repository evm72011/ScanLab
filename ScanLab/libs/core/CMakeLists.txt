set(LIB_NAME ${CORE_LIB_NAME})

add_library(${LIB_NAME} SHARED
    # todo mock
    src/acquisition/acquisition_control.cpp
    src/acquisition/ascan/a_scan_acquisition_source.cpp
    src/acquisition/ascan/a_scan_raw_decoder.cpp
    src/acquisition/ascan/a_scan_resampler.cpp
    src/acquisition/ascan/a_scan_cropper.cpp
    src/acquisition/ascan/a_scan_pipeline.cpp

    src/health/health_topology.cpp
    src/health/humidity_topology_api.cpp
    src/health/temperature_topology_api.cpp

    src/a_scan_acquisition.cpp # deprecated
)

# TODO: Replace WINDOWS_EXPORT_ALL_SYMBOLS with explicit export macros (e.g. SL_CORE_API).
# Currently all symbols are exported automatically, which is not suitable for a stable/public API.
# Introduce export header and mark only intended public classes/functions.
set_target_properties(${LIB_NAME} PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

set(IMPL_VARIANT "")

if(MOCK_DEVICE)
    set(IMPL_VARIANT "mock/")
    target_compile_definitions(${LIB_NAME} PRIVATE MOCK_DEVICE=1)
endif()

target_sources(${LIB_NAME} PRIVATE
    src/device/${IMPL_VARIANT}device.cpp
    src/health/${IMPL_VARIANT}humidity_reader.cpp
    src/health/${IMPL_VARIANT}temperature_reader.cpp
)

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
