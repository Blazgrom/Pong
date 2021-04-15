
set(SOURCE_FILES
src/Pong.cpp
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES}) 

set(HEADER_FILES
    include/Pong/GameLayer.hpp
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES}) 

set(EXE_SOURCE_FILES
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

