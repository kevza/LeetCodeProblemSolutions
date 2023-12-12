#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>

using namespace std;

class Solution {
public:
  string longestPalindrome(string s) {
    int max_length = 1;
    int n = s.length();
    int start = 0;
    for (int i = 0; i < s.size(); i++)
    {
      int l = i;
      int r = i;
      while (r < n - 1 && s[r] == s[r + 1])
      {
        r++;
      }
      i = r;
      while (l > 0 && r < n - 1 && s[l - 1] == s[r + 1])
      {
        l--;
        r++;
      }
      if (max_length < r - l + 1)
      {
        start = l;
        max_length =  r - l + 1;
      }
    }

    return s.substr(start, max_length);
  }
};

struct TestParams {
  string input;
  string output;
};

ostream &operator<<(ostream &os, const TestParams &params) {
  os << "Input : " << params.input;
  return os;
}

class TestSortedMedian : public testing::TestWithParam<TestParams> {};

TEST_P(TestSortedMedian, cases) {
  TestParams p = GetParam();
  Solution s;
  EXPECT_EQ(p.output, s.longestPalindrome(p.input))
      << p << " - Failed";
}

INSTANTIATE_TEST_SUITE_P(
    MedianTests, TestSortedMedian,
    testing::Values(
      (TestParams){"aacabdkacaa", "aca"},
      (TestParams){"ccc", "ccc"},
      (TestParams){"a", "a"},
      (TestParams){"babad", "bab"},
      (TestParams){"cbbd", "bb"},
      (TestParams){"HelloWorlddlroWolleH", "HelloWorlddlroWolleH"},
      (TestParams){"bb", "bb"}));
