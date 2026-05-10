function(add_clang_tidy)
    set(oneValueArgs TARGET ENABLE)

    cmake_parse_arguments(
        ACLT
        ""
        "${oneValueArgs}"
        ""
        ${ARGN}
    )

    if(NOT TARGET ${ACLT_TARGET})
        message(FATAL_ERROR "add_clang_tidy: Target '${ACLT_TARGET}' does not exist.")
        return()
    endif()

    if(NOT ACLT_ENABLE)
        message(STATUS "Clang-Tidy deactivated for ${ACLT_TARGET}")
        return()
    endif()

    get_target_property(TARGET_SOURCES ${ACLT_TARGET} SOURCES)

    if(NOT TARGET_SOURCES)
        message(WARNING "No sources found for target: ${ACLT_TARGET}")
        return()
    endif()

    list(
        FILTER
        TARGET_SOURCES
        INCLUDE
        REGEX
        ".*\\.(cc|cxx|cpp|h|hpp)$"
    )

    list(
        FILTER
        TARGET_SOURCES
        EXCLUDE
        REGEX
        ".*_autogen/.*|.*mocs_compilation\\.cpp$|.*qmlcache.*|.*\\.rcc/.*|.*qrc_.*\\.cpp$"
    )

    set(ABS_TARGET_SOURCES)

    foreach(source IN LISTS TARGET_SOURCES)
        if(IS_ABSOLUTE "${source}")
            set(abs_source "${source}")
        else()
            set(abs_source "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
        endif()

        string(FIND "${abs_source}" "${CMAKE_BINARY_DIR}" is_in_build_dir)

        if(is_in_build_dir EQUAL -1)
            list(APPEND ABS_TARGET_SOURCES "${abs_source}")
        endif()
    endforeach()

    if(NOT ABS_TARGET_SOURCES)
        message(WARNING "No clang-tidy sources left for target: ${ACLT_TARGET}")
        return()
    endif()

    find_package(
        Python3
        COMPONENTS Interpreter
        REQUIRED
    )

    find_program(CLANGTIDY clang-tidy)

    if(NOT CLANGTIDY)
        message(WARNING "CLANGTIDY NOT FOUND")
        return()
    endif()

    add_custom_target(
        ${ACLT_TARGET}_clangtidy
        COMMAND
            ${Python3_EXECUTABLE}
            ${CMAKE_SOURCE_DIR}/scripts/run-clang-tidy.py
            ${ABS_TARGET_SOURCES}
            -p ${CMAKE_BINARY_DIR}
            -config-file ${CMAKE_SOURCE_DIR}/.clang-tidy
            -extra-arg=-Wno-everything
            -extra-arg=-Wunused-variable
            -extra-arg=-Wunused-variable
            -extra-arg=-Wno-c++98-compat
            -extra-arg=-Wno-c++98-compat-pedantic
            -extra-arg=-Wno-pre-c++17-compat
            -quiet
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        USES_TERMINAL
    )

    message(STATUS "Added Clang Tidy for Target: ${ACLT_TARGET}")
endfunction()