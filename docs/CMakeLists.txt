
configure_file(doxy.in doxy.cfg @ONLY)

add_custom_target(
    docs 
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxy.cfg
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    VERBATIM
    SOURCES
)
message("Create documentation by using the `docs` target")
