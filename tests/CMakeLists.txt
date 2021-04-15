project(${CMAKE_PROJECT_NAME}Tests)


set(TEST_SOURCES
    "src/test.cpp"
)

find_package(Catch2 CONFIG REQUIRED)
add_executable(${PROJECT_NAME} ${TEST_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include include)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_LIB_NAME}  Catch2::Catch2)

add_test(
    NAME 
    ${PROJECT_NAME}
    COMMAND
    ${PROJECT_NAME}
)