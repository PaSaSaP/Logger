cmake_minimum_required(VERSION 3.6)
project(logger-tests)

set(CMAKE_CXX_STANDARD 14)
find_package(GTest REQUIRED)

add_executable(tests test1.cc)
target_link_libraries(tests GTest::GTest GTest::Main)

add_test(Tests tests)

