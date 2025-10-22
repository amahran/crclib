cmake_minimum_required(VERSION 3.22)
project(
  crclib
  VERSION 1.0.0
  DESCRIPTION "CRC Library implementaion in C"
  HOMEPAGE_URL "https://github.com/amahran/crclib.git"
  LANGUAGES C CXX)

option(${PROJECT_NAME}_ENABLE_TESTING "Enable Testing for the CRC Library"
       ${PROJECT_IS_TOP_LEVEL})

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
endif()

add_subdirectory(src)
target_include_directories(
  crc PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

if(PROJECT_IS_TOP_LEVEL)
  add_executable(${PROJECT_NAME} main.c)
  target_link_libraries(${PROJECT_NAME} PRIVATE crc)
endif()

if(${PROJECT_NAME}_ENABLE_TESTING)
  enable_testing()
  add_subdirectory(tests)
else()
  mark_as_advanced(${PROJECT_NAME}_ENABLE_TESTING)
endif()
