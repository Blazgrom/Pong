
set(SOURCE_FILES
    src/example.cpp
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES}) 

set(EXE_SOURCE_FILES
    src/main.cpp
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

set(HEADER_FILES
    include/projectname/test.hpp
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES}) 
