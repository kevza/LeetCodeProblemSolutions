#include <gtest/gtest.h>
#include <stack>
#include <string>

using namespace std;

namespace {
  class Solution
  {
  public:
    bool isMatch(string s, string p) {
        bool matches = true;
        stack<pair<int, int>> st;
        st.push(make_pair(0, 0));
        while (!st.empty())
        {
            auto [string_index, pattern_index] = st.top();
            st.pop();
            while (string_index < s.length() && pattern_index < p.length())
            {
                char _s = s[string_index];
                char _p = p[pattern_index];
                if (_p == '?' || _p == _s)
                {
                    string_index++;
                    pattern_index++;
                }
                else if (_p == '*')
                {
                    while (p[pattern_index] == '*') {
                      pattern_index++;
                    }
                    st.push(make_pair(string_index + 1, pattern_index - 1));
                }
                else 
                {
                  break; 
                }
            }

            if (string_index == s.length() && (pattern_index == p.length() || (pattern_index == p.length() - 1 && p[pattern_index] == '*')))
            {
                return true;
            }
        }
        return false;
    }
  };
}

struct Params {
  string s;
  string p;
  bool output;
};

class TestSolution : public testing::TestWithParam<Params> {
};

TEST_P(TestSolution, Test) {
  auto param = GetParam();
  auto s = Solution();
  EXPECT_EQ(param.output, s.isMatch(param.s, param.p));
}


INSTANTIATE_TEST_SUITE_P(LeetcodeSolution, TestSolution,
                         testing::Values( // (Params){"a", "a", true},
                                          // (Params){"", "", true},
                                          // (Params){"", "a", false},
                                          // (Params){"b", "a", false},
                                          (Params){"aba", "a*", true},
                                          (Params){"aba", "a*a", true}
                                         ));
