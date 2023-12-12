#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

class Solution {
public:
  string longestCommonPrefix(vector<string> &input) {
    int max = 0;
    bool ok = true;
    int i = 0;
    auto a = input.begin();
    while (input.size() > 1) {
      auto b = a;
      while ((++b) != input.end() && i < b->size() && i < a->size() &&
             (*b)[i] == (*a)[i]) {
      }
      if (i > max) {
        max = i;
      }

      if (b != input.end()) {
        return input.front().substr(0, max);
      }
      i++;
    }
    return input.size() == 1 ? input.front() : "";
  }
};

struct TestParams {
  string output;
  vector<string> input;
};

class TestBinarySearch : public testing::TestWithParam<TestParams> {};

TEST_P(TestBinarySearch, cases) {
  TestParams p = GetParam();
  Solution s;
  EXPECT_EQ(p.output, s.longestCommonPrefix(p.input)) << " - Failed";
}

INSTANTIATE_TEST_SUITE_P(
    MedianTests, TestBinarySearch,
    testing::Values((TestParams){"fl", {"flower", "flow", "flight"}},
                    (TestParams){"", {"", ""}}, (TestParams){"", {""}},
                    (TestParams){"a", {"a"}}, (TestParams){"aa", {"aa", "aa"}},
                    (TestParams){"", {"dog", "racecar", "car"}}));
