#include <gtest/gtest.h>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

namespace {
  class Solution
  {
  public:
    bool isMatch(string s, string p) {
        bool matches = true;
        stack<pair<int, int>> st;
        bool checked[s.length()][p.length()];
        fill(&checked[0][0], &checked[s.length()][p.length()],false);
        

        st.push(make_pair(0, 0));
        while (!st.empty())
        {
            auto [string_index, pattern_index] = st.top();
            st.pop();
            if (checked[string_index][pattern_index])
            {
              continue;
            }
            checked[string_index][pattern_index] = true;

            bool testResult = true;
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
                  testResult = false;
                  break; 
                }
            }
           
            if (testResult)
            {
              while (p[pattern_index] == '*') {
                pattern_index++;
              }

              if (string_index == s.length() && pattern_index == p.length()) 
              {
                  return true;
              }
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
                         testing::Values( (Params){"a", "a", true},
                                          (Params){"", "", true},
                                          (Params){"", "a", false},
                                          (Params){"b", "a", false},
                                          (Params){"aba", "a*", true},
                                          (Params){"aba", "a*a", true},
                                          (Params){"abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb", "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb", false}
                                         ));
