add_library(crc STATIC)
target_sources(crc PRIVATE crc.c)
target_compile_features(crc PUBLIC c_std_99)
target_include_directories(crc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
