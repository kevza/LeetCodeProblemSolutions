#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

class Solution {
public:
  const multimap<char, char> vals = {
      {'2', 'a'}, {'2', 'b'}, {'2', 'c'},

      {'3', 'd'}, {'3', 'e'}, {'3', 'f'},

      {'4', 'g'}, {'4', 'h'}, {'4', 'i'},

      {'5', 'j'}, {'5', 'k'}, {'5', 'l'},

      {'6', 'm'}, {'6', 'n'}, {'6', 'o'},

      {'7', 'p'}, {'7', 'q'}, {'7', 'r'}, {'7', 's'},

      {'8', 't'}, {'8', 'u'}, {'8', 'v'},

      {'9', 'w'}, {'9', 'x'}, {'9', 'y'}, {'9', 'z'}};

  void helper(const string &digits, int i, string current_set,
              vector<string> &result) {
    i++;
    if (i < digits.length()) {
      auto range = vals.equal_range(digits[i]);
      for (auto it = range.first; it != range.second; it++) {
        helper(digits, i, current_set + it->second, result);
      }
    } else {
      if (!current_set.empty()) {
        result.push_back(current_set);
      }
    }
  }

  vector<string> letterCombinations(string digits) {
    vector<string> result;
    helper(digits, -1, string(), result);
    return result;
  }
};

struct TestParams {
  string input;
  vector<string> output;
};

class TestBinarySearch : public testing::TestWithParam<TestParams> {};

TEST_P(TestBinarySearch, cases) {
  TestParams p = GetParam();
  Solution s;
  EXPECT_EQ(p.output, s.letterCombinations(p.input)) << " - Failed";
}

INSTANTIATE_TEST_SUITE_P(
    MedianTests, TestBinarySearch,
    testing::Values(
        (TestParams){"", {}},
        (TestParams){"23",
                     {"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"}},
        (TestParams){"2", {"a", "b", "c"}},
        (TestParams){"22",
                     {"aa", "ab", "ac", "ba", "bb", "bc", "ca", "cb", "cc"}}

        ));
