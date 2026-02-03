cmake_minimum_required(VERSION 3.20)
project(tester_app LANGUAGES CXX)

add_executable(tester_app main.cpp)

set(OEMPA_SDK_DIR ${CMAKE_SOURCE_DIR}/third_party/OEMPA)

target_include_directories(tester_app PRIVATE
    ${OEMPA_SDK_DIR}/include
)

file(GLOB OEMPA_LIBS
    ${OEMPA_SDK_DIR}/x64/release/*.lib
)

target_link_libraries(tester_app PRIVATE ${OEMPA_LIBS})

# copy dlls
add_custom_command(
    TARGET tester_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${OEMPA_SDK_DIR}/x64/release/OEMPA.dll
        $<TARGET_FILE_DIR:tester_app>
)
