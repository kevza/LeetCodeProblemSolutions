#include <gtest/gtest.h>
#include <vector>

using namespace std;

namespace {
class Solution {
public:
  int firstMissingPositive(vector<int> &nums) {
    int n = nums.size();
    vector<int> a(n, 0);
    for (auto v : nums) {
      int64_t i = (int64_t)v - 1;
      if (i >= 0 && i < n) {
        a[i] = 1;
      }
    }
    for (int i = 0; i < n; i++) {
      if (a[i] == 0) {
        return i + 1;
      }
    }
    return nums.size() + 1;
  }
};
} // namespace

struct Params {
  vector<int> input;
  int output;
};

class TestSolution : public testing::TestWithParam<Params> {};

TEST_P(TestSolution, Test) {
  auto param = GetParam();
  auto s = Solution();
  EXPECT_EQ(param.output, s.firstMissingPositive(param.input));
}

INSTANTIATE_TEST_SUITE_P(LeetcodeSolution, TestSolution,
                         testing::Values((Params){{1, 2, 0}, 3},
                                         (Params){{7, 8, 9, 11, 12}, 1},
                                         (Params){{1}, 2}));
