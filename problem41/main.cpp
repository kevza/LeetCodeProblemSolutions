#include <gtest/gtest.h>
#include <vector>

using namespace std;

namespace {
class Solution {
public:
  int firstMissingPositive(vector<int> &nums) {
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      int64_t next = (int64_t)nums[i] - 1;
      nums[i] = -1;
      while (next >= 0 && next < n && next != nums[next] - 1) {
        int t = nums[next] - 1;
        nums[next] = next + 1;
        next = t;
      }
    }
    for (int i = 0; i < n; i++) {
      if (nums[i] < 0) {
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
                         testing::Values((Params){{1, 1}, 2},
                                         (Params){{3, 4, -1, 1}, 2},
                                         (Params){{1, 2, 0}, 3},
                                         (Params){{7, 8, 9, 11, 12}, 1},
                                         (Params){{1}, 2}));
