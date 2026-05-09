function(add_cmake_format_target)
    if(NOT ENABLE_CMAKE_FORMAT)
        return()
    endif()

    if(WIN32)
        set(VENV_PYTHON "${VENV_DIR}/Scripts/python.exe")
    else()
        set(VENV_PYTHON "${VENV_DIR}/bin/python")
    endif()

    if(EXISTS "${VENV_PYTHON}")
        set(PYTHON_EXE "${VENV_PYTHON}")
    else()
        find_package(Python3 REQUIRED COMPONENTS Interpreter)
        set(PYTHON_EXE "${Python3_EXECUTABLE}")
    endif()

    add_custom_target(
        run_cmake_format
        COMMAND
            ${CMAKE_COMMAND} -E env "VENV_DIR=${VENV_DIR}" "${PYTHON_EXE}"
            "${CMAKE_SOURCE_DIR}/scripts/run-cmake-format.py"
            "${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/.cmake-format.yaml"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        USES_TERMINAL)

    message(STATUS "Added cmake-format target: run_cmake_format")
endfunction()
