cmake_minimum_required (VERSION 2.6)
project (Test)
include_directories ("${PROJECT_SOURCE_DIR}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=gnu++11")

add_executable(Test testing.cpp)

target_link_libraries(Test gtest pthread)
