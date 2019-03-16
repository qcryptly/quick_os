#include "test.hxx"
#include "crc32.h"

TEST(Test, EFI_CRC32_NOT_EMPTY) {
  std::string fixture{"ThisIsATest"};
  std::uint32_t expected = 3547384400;
  std::uint32_t result{};
  crc32(fixture.data(), fixture.size(), &result);
  EXPECT_EQ(result, expected);
}

TEST(Test, EFI_CRC32_EMPTY) {
  std::string fixture{""};
  std::uint32_t expected = 0;
  std::uint32_t result{};
  crc32(fixture.data(), fixture.size(), &result);
  EXPECT_EQ(result, expected);
}
