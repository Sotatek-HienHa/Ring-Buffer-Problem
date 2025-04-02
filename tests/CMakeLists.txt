cmake_minimum_required(VERSION 2.6)

find_package(GTest REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GTEST_INCLUDE_DIRS})
 
add_executable(runTests gtest.cpp ringbuffer.c)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)