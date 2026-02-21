cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(tester_app LANGUAGES CXX)

add_executable(tester_app main.cpp)

set(OEMPA_SDK_DIR "C:/ProgramData/AOS/OEMPA 1.3.0.2/Sources")

target_include_directories(tester_app PRIVATE
    ${OEMPA_SDK_DIR}/Common
    ${OEMPA_SDK_DIR}/UserHeaders/x64
)

set(OEMPA_BIN_DIR "${OEMPA_SDK_DIR}/UTKernel/x64/Release")

file(GLOB OEMPA_LIBS
    "${OEMPA_BIN_DIR}/*.lib"
)
target_link_directories(tester_app PRIVATE "${OEMPA_BIN_DIR}")
target_link_libraries(tester_app PRIVATE ${OEMPA_LIBS})

# copy dlls
file(GLOB OEMPA_DLLS CONFIGURE_DEPENDS
    "${OEMPA_BIN_DIR}/*.dll"
)

add_custom_command(TARGET tester_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${OEMPA_DLLS}
            "$<TARGET_FILE_DIR:tester_app>"
)

#add_custom_command(TARGET tester_app POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:tester_app>"
#)

#foreach(dll ${OEMPA_DLLS})
#    add_custom_command(TARGET tester_app POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            "${dll}"
#            "$<TARGET_FILE_DIR:tester_app>/$<IF:$<BOOL:${dll}>,${CMAKE_MATCH_0},>"
#    )
#endforeach()