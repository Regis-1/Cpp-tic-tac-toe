cmake_minimum_required(VERSION 3.26)

project(Cpp-ttt)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(extlibs)
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Game.cpp
    src/State.cpp
    src/MenuState.cpp
    src/MatchState.cpp
    src/MatchmakingState.cpp
    src/Player.cpp
    src/HumanPlayer.cpp
    src/OnlinePlayer.cpp
)
target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} asio)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif()
