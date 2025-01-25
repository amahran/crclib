add_executable(CrcGTestCases test_crc.cc)

find_package(GTest REQUIRED)
target_link_libraries(CrcGTestCases PRIVATE GTest::gtest crc)

gtest_discover_tests(CrcGTestCases)
