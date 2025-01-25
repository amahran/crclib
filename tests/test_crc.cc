#include <gtest/gtest.h>

#include <vector>

#include "crc.h"

/// @brief CRC 32 parameters
#define CRC32_INIT_VAL 0xFFFFFFFFUL
#define CRC32_POLYNOMIAL 0xEDB88320UL  // IEEE-802.3
#define CRC32_FINAL_XOR 0xFFFFFFFFUL

// Mock function to simulate the cyclic function behavior
static int g_cyclic_call_count = 0;
static void mock_cyclicfn() { g_cyclic_call_count++; }

// Test CRC initialization
TEST(CrcTest, InitTest) {
    struct crc_ctx crc32_ctx{
        0, nullptr, {CRC32_INIT_VAL, CRC32_POLYNOMIAL, CRC32_FINAL_XOR}, {0}};

    crc_init(&crc32_ctx);

    EXPECT_EQ(crc32_ctx.crc, 0xFFFFFFFF);
}

// Test CRC update with known data
TEST(CrcTest, UpdateTest) {
    struct crc_ctx crc32_ctx{
        0, nullptr, {CRC32_INIT_VAL, CRC32_POLYNOMIAL, CRC32_FINAL_XOR}, {0}};

    crc_init(&crc32_ctx);

    const std::vector<uint8_t> data = {0x31, 0x32, 0x33, 0x34};  // "1234"
    crc_update(&crc32_ctx, data.data(), data.size());
    crc_finalize(&crc32_ctx);

    EXPECT_EQ(crc32_ctx.crc, 0x9BE3E0A3);
}

// Test CRC generation table with cyclic function callback
TEST(CrcTest, CyclicFunctionTableGenerationTest) {
    g_cyclic_call_count = 0;

    struct crc_ctx crc32_ctx{
        0,
        mock_cyclicfn,
        {CRC32_INIT_VAL, CRC32_POLYNOMIAL, CRC32_FINAL_XOR},
        {0}};

    crc_init(&crc32_ctx);

    // Check that the cyclic function was called during table generation
    EXPECT_EQ(g_cyclic_call_count, 256 / CRC_CYCLIC_TRIGGER_INTERVAL);
}

// Test CRC update with the cyclic function callback
TEST(CrcTest, CyclicFunctionUpdateTest) {
    struct crc_ctx crc32_ctx{
        0,
        mock_cyclicfn,
        {CRC32_INIT_VAL, CRC32_POLYNOMIAL, CRC32_FINAL_XOR},
        {0}};

    crc_init(&crc32_ctx);
    g_cyclic_call_count = 0;

    const std::vector<uint8_t> data = {0x31, 0x32, 0x33, 0x34, 0x35};
    crc_update(&crc32_ctx, data.data(), data.size());
    crc_finalize(&crc32_ctx);

    EXPECT_EQ(g_cyclic_call_count,
              (data.size() + CRC_CYCLIC_TRIGGER_INTERVAL - 1) /
                  CRC_CYCLIC_TRIGGER_INTERVAL);
}

// Test CRC with empty data
TEST(CrcTest, EmptyDataTest) {
    struct crc_ctx crc32_ctx{
        0, nullptr, {CRC32_INIT_VAL, CRC32_POLYNOMIAL, CRC32_FINAL_XOR}, {0}};

    crc_init(&crc32_ctx);

    std::vector<uint8_t> data;
    crc_update(&crc32_ctx, data.data(), data.size());
    crc_finalize(&crc32_ctx);

    EXPECT_EQ(crc32_ctx.crc, 0);
}

// Test CRC with single-byte data
TEST(CrcTest, SingleByteTest) {
    struct crc_ctx crc32_ctx{
        0, nullptr, {CRC32_INIT_VAL, CRC32_POLYNOMIAL, CRC32_FINAL_XOR}, {0}};

    crc_init(&crc32_ctx);

    const std::vector<uint8_t> data = {0x31};  // "1"
    crc_update(&crc32_ctx, data.data(), data.size());
    crc_finalize(&crc32_ctx);

    EXPECT_EQ(crc32_ctx.crc, 0x83DCEFB7);
}

// Test CRC with large data
TEST(CrcTest, LargeDataTest) {
    struct crc_ctx crc32_ctx{
        0, nullptr, {CRC32_INIT_VAL, CRC32_POLYNOMIAL, CRC32_FINAL_XOR}, {0}};

    crc_init(&crc32_ctx);

    // Large data buffer
    const std::vector<uint8_t> data(1024UL * 1024, 0xAB);
    crc_update(&crc32_ctx, data.data(), data.size());
    crc_finalize(&crc32_ctx);

    EXPECT_EQ(crc32_ctx.crc, 0xB8CC1630);
}

// Main function for running the tests
auto main(int argc, char** argv) -> int {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
