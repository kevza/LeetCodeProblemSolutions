#include <gtest/gtest.h>
#include <vector>

using namespace std;

namespace {
class Solution {
public:
  int searchInsert(vector<int> &nums, int target) {
    int start = 0;
    int end = nums.size();
    while (start < end) {
      int i = (start + end) / 2;
      if (nums[i] < target) {
        start = i + 1;
      } else if (nums[i] > target) {
        end = i;
      } else {
        return i;
      }
    }
    return start;
  }
};
} // namespace

struct Params {
  vector<int> input;
  int target;
  int output;
};

class TestSolution : public testing::TestWithParam<Params> {};

TEST_P(TestSolution, Test) {
  auto param = GetParam();
  auto s = Solution();
  EXPECT_EQ(param.output, s.searchInsert(param.input, param.target));
}

INSTANTIATE_TEST_SUITE_P(LeetcodeSolution, TestSolution,
                         testing::Values((Params){{}, 0, 0},
                                         (Params){{2}, 1, 0},
                                         (Params){{2}, 3, 1},
                                         (Params){{1, 3, 5, 6}, 5, 2},
                                         (Params){{1, 3, 4, 5}, 2, 1},
                                         (Params){{1, 3, 5, 6}, 7, 4}));
