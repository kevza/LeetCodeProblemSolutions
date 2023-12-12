#include "gtest/gtest.h"
#include <climits>
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>

using namespace std;

class Solution {
public:
  int threeSumClosest(const vector<int> &list, int target) {
    int n = list.size();
    int result = 0;
    int d_c = INT_MAX;
    vector<int> sorted_list(list.begin(), list.end());
    sort(sorted_list.begin(), sorted_list.end());
    for (int i = 1; i < n - 1; i++) {
      int l = 0;
      int r = list.size() - 1;
      while (l < i && r > i) {
        int a = sorted_list[l];
        int b = sorted_list[i];
        int c = sorted_list[r];
        int sum = a + b + c;
        int d_sum = 0;
        if (sum > target) {
          r--;
          d_sum = sum - target;
        }

        if (sum < target) {
          l++;
          d_sum = target - sum;
        }

        if (sum == target) {
          return sum;
        }

        if (d_sum < d_c) {
          d_c = d_sum;
          result = sum;
        }
      }
    }

    return result;
  }
};

struct TestParams {
  vector<int> input;
  int target;
  int output;
};

class TestBinarySearch : public testing::TestWithParam<TestParams> {};

TEST_P(TestBinarySearch, cases) {
  TestParams p = GetParam();
  Solution s;
  EXPECT_EQ(p.output, s.threeSumClosest(p.input, p.target)) << " - Failed";
}

INSTANTIATE_TEST_SUITE_P(
    MedianTests, TestBinarySearch,
    testing::Values((TestParams){{4, 0, 5, -5, 3, 3, 0, -4, -5}, -2, -2},
                    (TestParams){{0, 1, 2}, 3, 3},
                    (TestParams){{-1, 2, 1, -4}, 1, 2},
                    (TestParams{{0, 0, 0}, 1, 0})));
