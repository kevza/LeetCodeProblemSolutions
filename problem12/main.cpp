#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

class Solution {
public:
  // string intToRoman(int num) {
  //   vector<pair<int, string>> m = {
  //       {1000, "M"}, {900, "XM"}, {500, "D"}, {400, "CD"}, {100, "C"},
  //       {90, "XC"},  {50, "L"},   {40, "XL"}, {10, "X"},   {9, "IX"},
  //       {5, "V"},    {4, "IV"},   {1, "I"}};

  //   string r;
  //   for (const auto &v : m) {
  //     int temp = num;
  //     while (temp > 0) {
  //       temp -= v.first;
  //       if (temp >= 0) {
  //         r += v.second;
  //         num -= v.first;
  //       }
  //     }
  //   }

  //   return r;
  // }

  int romanToInt(string input) {
    int nums[256];
    nums['M'] = 1000;
    nums['D'] = 500;
    nums['C'] = 100;
    nums['L'] = 50;
    nums['X'] = 10;
    nums['V'] = 5;
    nums['I'] = 1;

    int r = 0;

    for (int i = 0; i < input.length(); i++) {
      int a = nums[input[i]];
      int b = 0;
      if (i + 1 < input.length()) {
        b = nums[input[i + 1]];
      }
      if (a < b) {
        a = b - a;
        i++;
      }
      r += a;
    }

    return r;
  }
};

struct TestParams {
  int output;
  string input;
};

class TestBinarySearch : public testing::TestWithParam<TestParams> {};

TEST_P(TestBinarySearch, cases) {
  TestParams p = GetParam();
  Solution s;
  EXPECT_EQ(p.output, s.romanToInt(p.input)) << " - Failed";
}

INSTANTIATE_TEST_SUITE_P(
    MedianTests, TestBinarySearch,
    testing::Values((TestParams){1, "I"}, (TestParams){2, "II"},
                    (TestParams){3, "III"}, (TestParams){4, "IV"},
                    (TestParams){5, "V"}, (TestParams){6, "VI"},
                    (TestParams){1, "I"}, (TestParams){25, "XXV"},
                    (TestParams){96, "XCVI"}));
