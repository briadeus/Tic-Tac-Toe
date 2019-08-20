cmake_minimum_required(VERSION 3.7)

set(GTEST_ROOT /usr/lib/gtest)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(testRunner testRunner.cpp)
target_link_libraries(testRunner ${GTEST_LIBRARIES} pthread)