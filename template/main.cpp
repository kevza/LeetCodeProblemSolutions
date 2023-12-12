#include <gtest/gtest.h>

namespace {
  class Solution {
    public:
      bool test(int arg) {
        return true;
      }
  };
}

struct Params {
  int input;
  bool output;
};

class TestSolution : public testing::TestWithParam<Params> {
};

TEST_P(TestSolution, Test) {
  auto param = GetParam();
  auto s = Solution();
  EXPECT_EQ(param.output, s.test(param.input));
}


INSTANTIATE_TEST_SUITE_P(LeetcodeSolution, TestSolution,
                         testing::Values((Params){0, true}));
