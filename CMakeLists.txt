cmake_minimum_required(VERSION 3.6)
project(Logger)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/include)
set(SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/OutputLogger.cpp
        ${CMAKE_SOURCE_DIR}/src/LoggerInterface.cpp
        ${CMAKE_SOURCE_DIR}/src/loggers.cpp 
	${CMAKE_SOURCE_DIR}/src/DatabaseLogger.cpp
)

add_library(logger SHARED ${SOURCE_FILES})
