cmake_minimum_required(VERSION 3.6)
project(Logger)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.h")

add_library(logger SHARED ${SOURCE_FILES})
