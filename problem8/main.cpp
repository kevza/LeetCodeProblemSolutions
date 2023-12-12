#include "limits.h"
#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

class Solution {
public:
  int myAtoi(string s) {
    int m = 1;
    long long r = 0;
    int i = 0;
    for (; i < s.length(); i++) {
      char c = s[i];
      if (c == '-') {
        m = -1;
        i++;
        break;
      } else if (c == '+') {
        i++;
        break;
      } else if (c != ' ') {
        break;
      }
    }

    for (; i < s.length(); i++) {
      char c = s[i];
      if (c >= '0' && c <= '9') {
        r *= 10;
        r += c - '0';
      } else {
        break;
      }
    }

    r *= m;
    r = r > INT_MAX ? INT_MAX : r;
    r = r < INT_MIN ? INT_MIN : r;
    return r;
  }
};

struct TestParams {
  string input;
  int output;
};

class TestBinarySearch : public testing::TestWithParam<TestParams> {};

TEST_P(TestBinarySearch, cases) {
  TestParams p = GetParam();
  Solution s;
  EXPECT_EQ(p.output, s.myAtoi(p.input)) << " - Failed";
}

INSTANTIATE_TEST_SUITE_P(
    MedianTests, TestBinarySearch,
    testing::Values((TestParams){"words and 987", 0}, (TestParams){"0", 0},
                    (TestParams){"00000-42a1234", 0}, (TestParams){"+", 0},
                    (TestParams){"-", 0}, (TestParams){"+-12", 0},
                    (TestParams){"-1", -1}, (TestParams){"1", 1},
                    (TestParams){"  2", 2}, (TestParams){"33", 33},
                    (TestParams){"-00033", -33}, (TestParams){"33abc", 33},
                    (TestParams){"-00033def55", -33}, (TestParams){"44", 44}));
