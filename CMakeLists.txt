cmake_minimum_required(VERSION 3.26)

project(Cpp-ttt)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(extlibs)
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Game.cpp
    src/State.cpp
)
target_link_libraries(${PROJECT_NAME} raylib)
