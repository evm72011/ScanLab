set(OEMPA_BIN_DIR "${OEMPA_SDK_DIR}/UTKernel/x64/Release")

IF(OEMPA_ENABLE)
    # copy dlls
    file(GLOB OEMPA_DLLS CONFIGURE_DEPENDS
        "${OEMPA_BIN_DIR}/*.dll"
    )
    
    add_custom_target(oempa_copy_dlls ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${OEMPA_DLLS} "${CMAKE_BINARY_DIR}"
        COMMENT "Copying OEMPA DLLs to ${CMAKE_BINARY_DIR}"
        VERBATIM
    )
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

    
    target_include_directories(${TAO_TARGET} PRIVATE
        ${OEMPA_SDK_DIR}/Common
        ${OEMPA_SDK_DIR}/UserHeaders/x64
    )
 
    set(OEMPA_BIN_DIR "${OEMPA_SDK_DIR}/UTKernel/x64/Release")

    file(GLOB OEMPA_LIBS
        "${OEMPA_BIN_DIR}/*.lib"
    )
    target_link_directories(${TAO_TARGET} PRIVATE "${OEMPA_BIN_DIR}")
    target_link_libraries(${TAO_TARGET} PRIVATE ${OEMPA_LIBS})
endfunction(target_add_oempa)
