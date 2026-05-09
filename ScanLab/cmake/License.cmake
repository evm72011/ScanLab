set(LICENSE_SRC "${CMAKE_SOURCE_DIR}/${SCANLAB_LICENSE_FILE}")
set(LICENSE_DST "$<TARGET_FILE_DIR:${APP_NAME}>/${SCANLAB_LICENSE_FILE}")

add_custom_target(
    copy_license ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${LICENSE_SRC}"
            "$<TARGET_FILE_DIR:${APP_NAME}>/${SCANLAB_LICENSE_FILE}"
    DEPENDS "${LICENSE_SRC}" ${APP_NAME}
    COMMENT "Copying license file")
