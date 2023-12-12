#include "gtest/gtest.h"
#include <deque>
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>

using namespace std;

class Solution {
public:
  bool isMatch(string s, string p) {
    vector<pair<int, int>> stack;
    stack.push_back(
        make_pair(-1, 0)); // first=string index, second = part index;
                           //
    int i = 0;
    int matching = 0;
    int m = s.length();
    int n = p.length();
    vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));
    while (!stack.empty()) {
      auto index_part = stack.back();
      stack.pop_back();
      // Increment index to access the next element
      i = index_part.first + 1;
      matching = index_part.second;
      while (i < m && matching < n) {
        // Check no further if this has already been explored
        if (memo[i][matching] != -1)
          break;

        if (matching < p.size() - 1 && p[matching + 1] == '*') {
          char c = p[matching];
          if (c == '.' || c == s[i]) {
            stack.push_back(make_pair(i, matching));
          }
          matching++;
        } else {
          char c = p[matching];
          if (c != '.' && c != s[i]) {
            break;
          }
          i++;
        }
        matching++;
      }
      // Have string length and all patterns used
      if (i == m && matching == n) {
        return true;
      }

      // Have string length and all remaining patterns are
      // wild cards
      if (i == m) {
        bool ok = true;
        for (int j = matching; j < n && ok; j++) {
          ok = ok && j < n - 1 && p[j + 1] == '*';
          if (ok)
            j++;
        }
        if (ok)
          return true;
      }
    }
    return false;
  }
};

struct TestParams {
  string input;
  string pattern;
  bool output;
};

class TestBinarySearch : public testing::TestWithParam<TestParams> {};

TEST_P(TestBinarySearch, cases) {
  TestParams p = GetParam();
  Solution s;
  EXPECT_EQ(p.output, s.isMatch(p.input, p.pattern)) << " - Failed";
}

INSTANTIATE_TEST_SUITE_P(
    MedianTests, TestBinarySearch,
    testing::Values(
        (TestParams){"aa", "a", false},
        (TestParams){"aabcbcbcaccbcaabc", ".*a*aa*.*b*.c*.*a*", true},
        (TestParams){"aa", "a*", true}, (TestParams){"aaa", "a*a", true},
        (TestParams){"aaa", "aaaa", false}, (TestParams){"aab", "c*a*b", true},
        (TestParams){"mississippi", "mis*is*p*.", false},
        (TestParams){"aa", "aa", true}));
