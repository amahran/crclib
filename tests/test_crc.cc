#include <gtest/gtest.h>

#include <cstdio>
#include <vector>

#include "crc.h"
#include "crc_cfg.h"

/// @brief CRC 32 parameters
#define CRC32_INIT_VAL 0xffffffffUL
#define CRC32_POLYNOMIAL 0xedb88320UL  // IEEE-802.3
#define CRC32_FINAL_XOR 0xffffffffUL

// Mock function to simulate the cyclic function behavior
static int g_cyclic_call_count = 0;
static void mock_cyclicfn() { g_cyclic_call_count++; }

// Test CRC initialization
TEST(CrcTest, InitTest) {
    Crc_Ctx crc32_ctx{
        0, nullptr, {CRC32_INIT_VAL, CRC32_POLYNOMIAL, CRC32_FINAL_XOR}, {0}};

    crc_init(&crc32_ctx);

    EXPECT_EQ(crc32_ctx.crc, 0xffffffff);
}

// Test CRC update with known data
TEST(CrcTest, UpdateTest) {
    Crc_Ctx crc32_ctx{
        0, nullptr, {CRC32_INIT_VAL, CRC32_POLYNOMIAL, CRC32_FINAL_XOR}, {0}};

    crc_init(&crc32_ctx);

    const std::vector<uint8_t> data = {0x31, 0x32, 0x33, 0x34};  // "1234"
    crc_update(&crc32_ctx, data.data(), data.size());
    crc_finalize(&crc32_ctx);

    EXPECT_EQ(crc32_ctx.crc, 0x9be3e0a3);
}

// Test CRC generation table with cyclic function callback
TEST(CrcTest, CyclicFunctionTableGenerationTest) {
    g_cyclic_call_count = 0;

    Crc_Ctx crc32_ctx{0,
                      mock_cyclicfn,
                      {CRC32_INIT_VAL, CRC32_POLYNOMIAL, CRC32_FINAL_XOR},
                      {0}};

    crc_init(&crc32_ctx);

    // Check that the cyclic function was called during table generation
    size_t table_size =
        sizeof(crc32_ctx._crc_table) / sizeof(crc32_ctx._crc_table[0]);
    EXPECT_EQ(g_cyclic_call_count,
              (table_size + CRC_CYCLIC_TRIGGER_INTERVAL - 1) /
               CRC_CYCLIC_TRIGGER_INTERVAL);
}

// Test CRC update with the cyclic function callback
TEST(CrcTest, CyclicFunctionUpdateTest) {
    g_cyclic_call_count = 0;

    Crc_Ctx crc32_ctx{0,
                      mock_cyclicfn,
                      {CRC32_INIT_VAL, CRC32_POLYNOMIAL, CRC32_FINAL_XOR},
                      {0}};

    const std::vector<uint8_t> data(1024UL * 1024, 0xab);
    crc_update(&crc32_ctx, data.data(), data.size());

    EXPECT_EQ(g_cyclic_call_count,
              (data.size() + CRC_CYCLIC_TRIGGER_INTERVAL - 1) /
                  CRC_CYCLIC_TRIGGER_INTERVAL);
}

// Test CRC with empty data
TEST(CrcTest, EmptyDataTest) {
    Crc_Ctx crc32_ctx{
        0, nullptr, {CRC32_INIT_VAL, CRC32_POLYNOMIAL, CRC32_FINAL_XOR}, {0}};

    crc_init(&crc32_ctx);

    std::vector<uint8_t> data;
    crc_update(&crc32_ctx, data.data(), data.size());
    crc_finalize(&crc32_ctx);

    EXPECT_EQ(crc32_ctx.crc, 0);
}

// Test CRC with single-byte data
TEST(CrcTest, SingleByteTest) {
    Crc_Ctx crc32_ctx{
        0, nullptr, {CRC32_INIT_VAL, CRC32_POLYNOMIAL, CRC32_FINAL_XOR}, {0}};

    crc_init(&crc32_ctx);

    const std::vector<uint8_t> data = {0x31};  // "1"
    crc_update(&crc32_ctx, data.data(), data.size());
    crc_finalize(&crc32_ctx);

    EXPECT_EQ(crc32_ctx.crc, 0x83dcefb7);
}

// Test CRC with large data
TEST(CrcTest, LargeDataTest) {
    Crc_Ctx crc32_ctx{
        0, nullptr, {CRC32_INIT_VAL, CRC32_POLYNOMIAL, CRC32_FINAL_XOR}, {0}};

    crc_init(&crc32_ctx);

    // Large data buffer
    const std::vector<uint8_t> data(1024UL * 1024, 0xab);
    crc_update(&crc32_ctx, data.data(), data.size());
    crc_finalize(&crc32_ctx);

    EXPECT_EQ(crc32_ctx.crc, 0xb8cc1630);
}

// Main function for running the tests
auto main(int argc, char** argv) -> int {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
