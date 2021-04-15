cmake_minimum_required(VERSION 3.16.0)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


project(ProjectName VERSION 1.0.0 LANGUAGES CXX)
include(cmake/ProjectSettings.cmake)
include(cmake/CompilerWarnings.cmake)
include(cmake/PrecompiledHeaders.cmake)
include(cmake/SourceFiles.cmake)
include(cmake/Utility.cmake)
add_executable(${PROJECT_NAME} ${EXE_SOURCE_FILES} )
set_compiler_warnings(${PROJECT_NAME})
set_cpp_standard_properties(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)
target_precompile_headers(${PROJECT_NAME} PRIVATE ${PRECOMPILED_HEADERS})

include(cmake/StaticAnalyzers.cmake)



if(ENABLE_TESTING)
    #Create a static lib to be linked with the executable created by the testing lib
    set(PROJECT_LIB_NAME ${PROJECT_NAME}Lib)
    add_library(${PROJECT_LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
    set_compiler_warnings(${PROJECT_LIB_NAME})
    target_compile_features(${PROJECT_LIB_NAME} PUBLIC cxx_std_17)

    target_include_directories(${PROJECT_LIB_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
    enable_testing()
    add_subdirectory(tests)
endif()


include(cmake/Dependency.cmake)
include(cmake/Installation.cmake)