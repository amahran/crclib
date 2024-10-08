#include "crc.h"
#include <gtest/gtest.h>
#include <vector>

// Mock function to simulate the cyclic function behavior
static int g_cyclic_call_count = 0;
static void
mock_cyclicfn()
{
  g_cyclic_call_count++;
}

// Test CRC initialization
TEST(CrcTest, InitTest)
{
  crc_ctx_t ctx;

  crc_init(&ctx);

  EXPECT_EQ(ctx.crc, 0xFFFFFFFF);
}

// Test CRC update with known data
TEST(CrcTest, UpdateTest)
{
  crc_ctx_t ctx;

  crc_init(&ctx);

  const std::vector<uint8_t> data = { 0x31, 0x32, 0x33, 0x34 }; // "1234"
  crc_update(&ctx, data.data(), data.size());
  crc_finalize(&ctx);

  EXPECT_EQ(ctx.crc, 0x9BE3E0A3);
}

// Test CRC generation table with cyclic function callback
TEST(CrcTest, CyclicFunctionTableGenerationTest)
{
  g_cyclic_call_count = 0;

  crc_ctx_t ctx;
  ctx.cyclicfn = mock_cyclicfn;

  crc_init(&ctx);

  // Check that the cyclic function was called during table generation
  EXPECT_EQ(g_cyclic_call_count, 256 / CRC_CYCLIC_TRIGGER_INTERVAL);
}

// Test CRC update with the cyclic function callback
TEST(CrcTest, CyclicFunctionUpdateTest)
{
  crc_ctx_t ctx;
  ctx.cyclicfn = mock_cyclicfn;

  crc_init(&ctx);
  g_cyclic_call_count = 0;

  const std::vector<uint8_t> data = { 0x31, 0x32, 0x33, 0x34, 0x35 };
  crc_update(&ctx, data.data(), data.size());
  crc_finalize(&ctx);

  EXPECT_EQ(g_cyclic_call_count,
            (data.size() + CRC_CYCLIC_TRIGGER_INTERVAL - 1) /
              CRC_CYCLIC_TRIGGER_INTERVAL);
}

// Test CRC with empty data
TEST(CrcTest, EmptyDataTest)
{
  crc_ctx_t ctx;

  crc_init(&ctx);

  std::vector<uint8_t> data;
  crc_update(&ctx, data.data(), data.size());
  crc_finalize(&ctx);

  EXPECT_EQ(ctx.crc, 0);
}

// Test CRC with single-byte data
TEST(CrcTest, SingleByteTest)
{
  crc_ctx_t ctx;

  crc_init(&ctx);

  const std::vector<uint8_t> data = { 0x31 }; // "1"
  crc_update(&ctx, data.data(), data.size());
  crc_finalize(&ctx);

  EXPECT_EQ(ctx.crc, 0x83DCEFB7);
}

// Test CRC with large data
TEST(CrcTest, LargeDataTest)
{
  crc_ctx_t ctx;

  crc_init(&ctx);

  // Large data buffer
  const std::vector<uint8_t> data(1024UL * 1024, 0xAB);
  crc_update(&ctx, data.data(), data.size());
  crc_finalize(&ctx);

  EXPECT_EQ(ctx.crc, 0xB8CC1630);
}

// Main function for running the tests
auto
main(int argc, char** argv) -> int
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
