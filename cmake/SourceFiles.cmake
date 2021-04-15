
set(SOURCE_FILES
    src/Application.cpp 
    src/Pong/Player.cpp
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES}) 

set(HEADER_FILES
    include/Pong/GameLayer.hpp
    include/Pong/Player.hpp
    include/Pong/Score.hpp
    include/Pong/Ball.hpp
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES}) 

set(EXE_SOURCE_FILES
${SOURCE_FILES}
${HEADER_FILES}
)

