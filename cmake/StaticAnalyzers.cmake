if(ENABLE_CLANG_TIDY)
    find_program(CLANGTIDY clang-tidy)
    if(CLANGTIDY)
        set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
        message("Clang-Tidy finished setting up.")
    else()
        message(SEND_ERROR "Clang-Tidy requested but executable not found.")
    endif()
endif()

if(ENABLE_CLANG_FORMAT)
    find_program(CLANGFORMAT clang-format)
    add_custom_target(format COMMAND ${CLANGFORMAT} -i ${SOURCE_FILES} ${HEADER_FILES})
    set_target_properties(format
       PROPERTIES
       FOLDER "Utility"
    )
    message("Format the project by using the `format` target")
endif()