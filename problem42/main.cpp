#include <gtest/gtest.h>
#include <vector>
using namespace std;

namespace {
class Solution {
public:
  int trap(vector<int> &height) {
    int n = height.size();
    vector<int> left(n, 0);
    vector<int> right(n, 0);
    int m = 0;
    for (int i = 0; i < n; i++) {
      int h = height[i];
      left[i] = m - h;
      m = max(h, m);
    }
    m = 0;
    int sum = 0;
    for (int i = n - 1; i >= 0; i--) {
      int h = height[i];
      right[i] = m - h;
      m = max(h, m);
      sum += max(0, min(left[i], right[i]));
    }
    return sum;
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
  EXPECT_EQ(param.output, s.trap(param.input));
}

INSTANTIATE_TEST_SUITE_P(
    LeetcodeSolution, TestSolution,
    testing::Values((Params){{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}, 6},
                    (Params){{4, 2, 0, 3, 2, 5}, 9}));
