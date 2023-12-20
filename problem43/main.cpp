#include <algorithm>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
using namespace std;

namespace {
class Solution {
public:
  const string mulMap[10][10] = {
      {"0", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
      {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"},
      {"0", "2", "4", "6", "8", "10", "12", "14", "16", "18"},
      {"0", "3", "6", "9", "12", "15", "18", "21", "24", "27"},
      {"0", "4", "8", "12", "16", "20", "24", "28", "32", "36"},
      {"0", "5", "10", "15", "20", "25", "30", "35", "40", "45"},
      {"0", "6", "12", "18", "24", "30", "36", "42", "48", "54"},
      {"0", "7", "14", "21", "28", "35", "42", "49", "56", "63"},
      {"0", "8", "16", "24", "32", "40", "48", "56", "64", "72"},
      {"0", "9", "18", "27", "36", "45", "54", "63", "72", "81"}};

  string add(char a, char b) {
    char c = a + b - '0';
    char d = '\0';
    if (c > '9') {
      d = '1';
      c = c - ':' + '0';
    }
    stringstream ss;
    if (d) {
      ss << d;
    }
    ss << c;
    return ss.str();
  }

  void merge(int i, char b, string &res) {
    if (res.size() <= i) {
      res += b;
      return;
    }

    string r = add(res[i], b);
    if (r.length() > 1) {
      res[i] = r[1];
      merge(i + 1, r[0], res);
    } else {
      res[i] = r[0];
    }
  }

  string multiply(string num1, string num2) {
    string result;
    int n1 = num1.length() - 1;
    int n2 = num2.length() - 1;
    for (int i = 0; i < num1.length(); i++) {
      for (int j = 0; j < num2.length(); j++) {
        string r = mulMap[num1[n1 - i] - '0'][num2[n2 - j] - '0'];
        if (r.size() > 1) {
          merge(i + j, r[1], result);
          merge(i + j + 1, r[0], result);
        } else {
          merge(i + j, r[0], result);
        }
      }
    }
    reverse(result.begin(), result.end());
    auto it = result.begin();
    while (it < result.end() && *it == '0') {
      it++;
    }
    string copy(it, result.end());
    return copy == "" ? "0" : copy;
  }
};
} // namespace

struct Params {
  string num1;
  string num2;
  string output;
};

class TestSolution : public testing::TestWithParam<Params> {};

TEST_P(TestSolution, Test) {
  auto param = GetParam();
  auto s = Solution();
  EXPECT_EQ(param.output, s.multiply(param.num1, param.num2));
}

INSTANTIATE_TEST_SUITE_P(LeetcodeSolution, TestSolution,
                         testing::Values((Params){"1", "0", "0"},
                                         (Params){"1", "1", "1"},
                                         (Params){"123", "456", "56088"},
                                         (Params){"33", "33", "1089"}));
