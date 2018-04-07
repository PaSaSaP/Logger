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
set(SQLITE_MODERN_CPP_VERSION "3.2")
file(DOWNLOAD https://github.com/aminroosta/sqlite_modern_cpp/archive/v${SQLITE_MODERN_CPP_VERSION}.tar.gz
  ${CMAKE_CURRENT_BINARY_DIR}/SqliteModernCpp.tar.gz SHOW_PROGRESS
  EXPECTED_MD5 bcee63d497d3069ec4fdf30ffc8652c5)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/sqlite_modern_cpp-${SQLITE_MODERN_CPP_VERSION}/hdr
  COMMAND ${CMAKE_COMMAND} -E tar xf ${CMAKE_CURRENT_BINARY_DIR}/SqliteModernCpp.tar.gz
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/SqliteModernCpp.tar.gz
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Unpacking ${CMAKE_CURRENT_BINARY_DIR}/SqliteModernCpp.tar.gz"
  VERBATIM
  )
add_custom_target(sqlite_modern_cpp
  ALL
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/sqlite_modern_cpp-${SQLITE_MODERN_CPP_VERSION}/hdr
  )

# Project files.
set(SOURCE_FILES
  ${CMAKE_SOURCE_DIR}/src/DatabaseLogger.cpp
  ${CMAKE_SOURCE_DIR}/src/LoggerInterface.cpp
  ${CMAKE_SOURCE_DIR}/src/loggers.cpp
  ${CMAKE_SOURCE_DIR}/src/OutputLogger.cpp
  )

# Create library.
add_library(${CMAKE_PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${SQLITE_LIBRARIES})
target_include_directories(${CMAKE_PROJECT_NAME}
  PUBLIC ${CMAKE_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/sqlite_modern_cpp-${SQLITE_MODERN_CPP_VERSION}/hdr
  )

add_dependencies(${CMAKE_PROJECT_NAME} sqlite_modern_cpp)

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
include(CTest)
add_subdirectory(tests)

