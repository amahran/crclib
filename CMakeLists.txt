cmake_minimum_required(VERSION 3.22)
project(
  ccrc
  VERSION 1.0.0
  DESCRIPTION "CRC Library implementaion in C"
  HOMEPAGE_URL "https://github.com/amahran/crclib.git"
  LANGUAGES C CXX)

enable_testing()

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE crc)

add_subdirectory(src)
add_subdirectory(tests)
