find_library(PsspLogger_LIB
	NAMES	pssplogger
	PATHS ${CMAKE_CURRENT_LIST_DIR}/build
	NO_DEFAULT_PATH
)
set(PsspLogger_INCLUDE_DIR ${SqLiteModernCpp_INCLUDE_DIR} ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/build/sqlite_modern_cpp-3.2/hdr)
