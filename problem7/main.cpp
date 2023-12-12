#include <gtest/gtest.h>
#include <iostream>
#include <limits.h>

using namespace std;
// INT_MIN -2147483648
// INT_MAX 2147483647
//

class Solution {
public:
  static constexpr int max_low = INT_MAX % 10;
  static constexpr int max_high = INT_MAX / 10;
  static constexpr int min_low = INT_MIN % 10;
  static constexpr int min_high = INT_MIN / 10;

  int reverse(int x) {
    int i = 0;
    int r = 0;
    int bound = x > 0 ? INT_MAX : INT_MIN;
    bool ok = true;
    while (x != 0) {
      int v = x % 10;

      if (i == 9) {
        if (x > 0) {
          if (r > max_high)
            return 0;
          if (r == max_high && x > max_low)
            return 0;
        }

        if (x < 0) {
          if (r < min_high)
            return 0;
          if (r == min_high && x < min_low)
            return 0;
        }
      }

      x /= 10;
      i++;
      r = (r * 10);
      r += v;
    }
    return r;
  }
};

struct TestParams {
  int input;
  int output;
};

class TestBinarySearch : public testing::TestWithParam<TestParams> {};

TEST_P(TestBinarySearch, cases) {
  TestParams p = GetParam();
  Solution s;
  EXPECT_EQ(p.output, s.reverse(p.input)) << " - Failed";
}

INSTANTIATE_TEST_SUITE_P(
    MedianTests, TestBinarySearch,
    testing::Values((TestParams){1, 1}, (TestParams){12, 21},
                    (TestParams){-12, -21}, (TestParams){-1, -1},
                    (TestParams){2147483647, 0}, (TestParams){-2147483648, 0},
                    (TestParams){2147447412, 2147447412},
                    (TestParams){1534236469, 0},
                    (TestParams){-2147447412, -2147447412}));
