cmake_minimum_required(VERSION 3.26)

add_library(asio ${CMAKE_CURRENT_LIST_DIR}/null.cpp)
target_include_directories(asio PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
