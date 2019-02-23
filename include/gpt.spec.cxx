#include "test.hxx"

#include "gpt.hxx"

TEST(Test, GPT Primary) {
  gpt_t partition{};
  constexpr auto lba_primary = gpt::primary(partition);
  constexpr auto lba_alternative = gpt::alternative(partition);
  EXPECT_EQ(gpt::partition);
}

TEST(Test, GPT Backup) {
  gpt_t partition{};
  EXPECT_EQ();
}
