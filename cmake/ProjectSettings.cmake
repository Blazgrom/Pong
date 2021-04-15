option(ENABLE_TESTING "Enables testing via catch2 framework" OFF)
option(ENABLE_CLANG_TIDY "Enables clang-tidy validation during build" OFF)
option(ENABLE_CLANG_FORMAT "Enables automatically  formating the code via a specific target" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()


option(ENABLE_DOXYGEN "Enable Doxygen documentation builds of source." OFF)
if(ENABLE_DOXYGEN)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        add_subdirectory(${CMAKE_SOURCE_DIR}/docs)
    endif()
endif()