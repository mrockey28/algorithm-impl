cmake_minimum_required (VERSION 2.6)
project (Test)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_executable(Test testing.cpp ConvexHull.cpp)

target_link_libraries(Test gtest pthread)
