cmake_minimum_required(VERSION 3.6)
project(Logger)

set(CMAKE_CXX_STANDARD 17)

include(ExternalProject)
ExternalProject_Add(SqliteModernCpp
	PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external_source_dir/SqliteModernCpp
	GIT_REPOSITORY git@github.com:SqliteModernCpp/sqlite_modern_cpp.git
	CONFIGURE_COMMAND ./configure --prefix ${CMAKE_CURRENT_BINARY_DIR}/external
	BUILD_IN_SOURCE 1
)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/external/include)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.h")

add_library(logger SHARED ${SOURCE_FILES})
