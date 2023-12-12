#include <gtest/gtest.h>
#include <vector>
#include <string>

using namespace std;
namespace {
  class Solution {
    public:
    int longestValidParentheses(string s) {
        int n = s.length();
        vector<int> preScan(s.length() + 1, 0);
        int k = 0;
        int i = 0;
        while (i < n)
        {
            if (s[i] == ')') {
                k--;
            }
            else
            {
                k++;
            }
            i++;
            preScan[i] = k;
        }

        int longest = 0;
        for (i = 0; i < n - 1; i++) {
            int j = i + 1;
            while (j < n + 1) {
                if (preScan[j] < preScan[i]) {
                    break;
                }
                if (preScan[j] == preScan[i] && j - i > longest) {
                    longest = j - i;
                }
                j++;
            }
        }
        return longest;
    }
  };
}

struct Params {
  string input;
  int output;
};

class TestSolution : public testing::TestWithParam<Params> {
};

TEST_P(TestSolution, Test) {
  auto param = GetParam();
  auto s = Solution();
  EXPECT_EQ(param.output, s.longestValidParentheses(param.input));
}


INSTANTIATE_TEST_SUITE_P(LeetcodeSolution, TestSolution,
                         testing::Values(
                         (Params){"(()", 2},
                         (Params){")()())", 4}));
