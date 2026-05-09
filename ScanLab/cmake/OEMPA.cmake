set(OEMPA_BIN_DIR "${OEMPA_SDK_DIR}/UTKernel/x64/Release")

if(OEMPA_ENABLE)

    if(NOT DEFINED OEMPA_SDK_DIR OR OEMPA_SDK_DIR STREQUAL "")
        message(FATAL_ERROR "OEMPA_ENABLE=ON, but OEMPA_SDK_DIR is not set.")
    endif()

    if(NOT IS_DIRECTORY "${OEMPA_SDK_DIR}")
        message(
            FATAL_ERROR "OEMPA SDK directory does not exist: '${OEMPA_SDK_DIR}'"
        )
    endif()

    if(NOT IS_DIRECTORY "${OEMPA_BIN_DIR}")
        message(
            FATAL_ERROR "OEMPA bin directory does not exist: '${OEMPA_BIN_DIR}'"
        )
    endif()

    # copy dlls
    file(
        GLOB
        OEMPA_DLLS
        CONFIGURE_DEPENDS
        "${OEMPA_BIN_DIR}/*.dll")

    if(NOT OEMPA_DLLS)
        message(FATAL_ERROR "No OEMPA DLLs found in '${OEMPA_BIN_DIR}'")
    endif()

    add_custom_target(
        oempa_copy_dlls ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${OEMPA_DLLS}
                "${CMAKE_BINARY_DIR}"
        COMMENT "Copying OEMPA DLLs to ${CMAKE_BINARY_DIR}"
        VERBATIM)
endif()

function(target_add_oempa)
    set(oneValueArgs TARGET)
    cmake_parse_arguments(
        TAO
        "${options}"
        "${oneValueArgs}"
        ""
        ${ARGN})

    if(NOT TARGET ${TAO_TARGET})
        message(
            FATAL_ERROR
                "target_add_oempa: Target '${TAO_TARGET}' does not exist.")
        return()
    endif()

    if(NOT OEMPA_ENABLE)
        message(WARNING "OEMPA is disabled")
        return()
    endif()

    target_include_directories(
        ${TAO_TARGET} SYSTEM PRIVATE ${OEMPA_SDK_DIR}/Common
                                     ${OEMPA_SDK_DIR}/UserHeaders/x64)

    set(OEMPA_BIN_DIR "${OEMPA_SDK_DIR}/UTKernel/x64/Release")

    file(GLOB OEMPA_LIBS "${OEMPA_BIN_DIR}/*.lib")
    target_link_directories(${TAO_TARGET} PRIVATE "${OEMPA_BIN_DIR}")
    target_link_libraries(${TAO_TARGET} PRIVATE ${OEMPA_LIBS})
endfunction(target_add_oempa)
