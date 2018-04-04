cmake_minimum_required(VERSION 3.6)
project(logger)

set(CMAKE_CXX_STANDARD 14)

# Macro for creating symlinks.
macro(makeLink src dest target)
  add_custom_command(TARGET ${target} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${src} ${dest}
    DEPENDS  ${dest} COMMENT "mklink ${src} -> ${dest}")
endmacro()

# Options.
option(DEVELOPER_TOOLS "Enable some stuff for developers.")

include(cmake/FindSqlite.cmake)
if(NOT SQLITE_FOUND)
  message(FATAL_ERROR "Cannot find sqlite library!")
endif(NOT SQLITE_FOUND)

# Include external projects.
include(ExternalProject)
ExternalProject_Add(SqliteModernCpp
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external_source_dir/SqliteModernCpp
  GIT_REPOSITORY git@github.com:SqliteModernCpp/sqlite_modern_cpp.git
  GIT_TAG origin/dev
  BUILD_IN_SOURCE 0
  INSTALL_COMMAND ""
  )
include_directories(${CMAKE_CURRENT_BINARY_DIR}/external/include)

# Project files.
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.h")

# Create library.
add_library(${CMAKE_PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${SQLITE_LIBRARIES})

# If option is enabled then create Makefile that just call make from build directory.
# Create also symbolic link for compile_commands.json so ie. YCM (VIM plugin) can index code.
if(DEVELOPER_TOOLS)
  file(WRITE ${CMAKE_SOURCE_DIR}/Makefile
    "default:\n"
    "\t\t@make --no-print-directory -C ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_PROJECT_NAME}\n"
    "%:\n"
    "\t\t@make --no-print-directory -C ${CMAKE_CURRENT_BINARY_DIR} $@")
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  makeLink(${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
    ${CMAKE_PROJECT_NAME})
endif(DEVELOPER_TOOLS)

enable_testing()
add_subdirectory(tests)

