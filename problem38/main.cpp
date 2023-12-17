#include <gtest/gtest.h>
#include <sstream>
#include <string>
using namespace std;

namespace {
  class Solution {
    public:
      string convert(string s) {
        char last = s[0];
        int count = 0;
        stringstream ss;
        for (int i = 0; i < s.length(); i++)
        {
          if (s[i] == last) {
            count += 1;
          } else {
            ss << count << last;
            last = s[i];
            count = 1;
          }
        }
        ss << count << last;
        return ss.str();
      }

      string countAndSay(int n) {
        if (n == 1)
        {
          return "1";
        }
        
        string result = "1";
        for (int i = 0; i < n - 1; i++) 
        {
          result = convert(result);
        }

        return result;
      }
  };
}

struct Params {
  int input;
  string output;
};

class TestSolution : public testing::TestWithParam<Params> {
};

TEST_P(TestSolution, Test) {
  auto param = GetParam();
  auto s = Solution();
  EXPECT_EQ(param.output, s.countAndSay(param.input));
}


INSTANTIATE_TEST_SUITE_P(LeetcodeSolution, TestSolution,
                         testing::Values(
                            (Params){8, "1113213211"},
                            (Params){7, "13112221"},
                            (Params){6, "312211"},
                            (Params){5, "111221"},
                            (Params){4, "1211"},
                            (Params){3, "21"},
                            (Params){2, "11"},
                            (Params){1, "1"}));
