#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

class Solution {
public:
  string convert(string s, int numRows) {
    int n = s.length();
    string r(s);

    int k = 0;
    int inc = max(2 * numRows - 2, 1);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < n + inc; j += inc) {
        int t = j - i;
        if (t > 0 && t < n && i > 0 && i < numRows - 1) {
          r[k] = s[t];
          k++;
        }

        int p = j + i;
        if (p < n) {
          r[k] = s[p];
          k++;
        }
      }
    }
    return r;
  }
};

struct TestParams {
  string input;
  int rows;
  string output;
};

class TestBinarySearch : public testing::TestWithParam<TestParams> {};

TEST_P(TestBinarySearch, cases) {
  TestParams p = GetParam();
  Solution s;
  EXPECT_EQ(p.output, s.convert(p.input, p.rows)) << " - Failed";
}

INSTANTIATE_TEST_SUITE_P(
    MedianTests, TestBinarySearch,
    testing::Values((TestParams){"PAYPALISHIRING", 3, "PAHNAPLSIIGYIR"},
                    (TestParams){"a", 1, "a"},
                    (TestParams){"PAYPALISHIRING", 4, "PINALSIGYAHRPI"}));
