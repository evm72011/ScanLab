cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(test_oempa LANGUAGES CXX)

set(MAIN_TARGET ${PROJECT_NAME})

add_executable(${MAIN_TARGET} main.cpp)

set(OEMPA_SDK_DIR "C:/ProgramData/AOS/OEMPA 1.3.0.2/Sources")
set(OEMPA_ENABLE ON)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(OEMPA)

target_add_oempa(TARGET ${MAIN_TARGET})
