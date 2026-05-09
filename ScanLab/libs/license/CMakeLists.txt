set(LIB_NAME ${LICENSE_LIB_NAME})

find_package(nlohmann_json REQUIRED)
find_package(libsodium REQUIRED)


add_library(${LIB_NAME} src/payload.cpp
                        src/reader.cpp
                        src/ed25519_verifier.cpp
)

target_include_directories(${LIB_NAME}
                           PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(${LIB_NAME} PRIVATE
                           nlohmann_json::nlohmann_json
                           libsodium::libsodium
)

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
