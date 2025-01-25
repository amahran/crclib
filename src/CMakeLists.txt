add_library(crc STATIC crc.c)
target_include_directories(crc PUBLIC ${CMAKE_CURRENT_LIST_DIR})
