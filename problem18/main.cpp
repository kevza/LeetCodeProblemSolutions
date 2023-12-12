#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> fourSum(vector<int> &nums, int target) {
    int n = nums.size();
    vector<int> list(nums.begin(), nums.end());
    sort(list.begin(), list.end());
    set<vector<int>> result;
    for (int i = 0; i < n - 3; i++) {
      for (int j = n - 1; j > i + 2; j--) {
        int newTarget = target - (list[i] + list[j]);
        int k = i + 1;
        int l = j - 1;
        while (k < l) {
          int a = list[k];
          int b = list[l];
          int newSum = a + b;
          if (newSum < newTarget) {
            k++;
          } else if (newSum > newTarget) {
            l--;
          } else {
            result.insert({list[i], list[k], list[l], list[j]});
            k++;
            l--;
          }
        }
        while (i < n - 3 && list[i] == list[i + 1]) {
          i++;
        }
        while (j > i + 2 && list[j] == list[j - 1]) {
          j--;
        }
      }
    }
    return vector<vector<int>>(result.begin(), result.end());
  };
};

struct TestParams {
  vector<int> input;
  int target;
  vector<vector<int>> output;
};

class TestBinarySearch : public testing::TestWithParam<TestParams> {};

TEST_P(TestBinarySearch, cases) {
  TestParams p = GetParam();
  Solution s;
  EXPECT_EQ(p.output, s.fourSum(p.input, p.target)) << " - Failed";
}

INSTANTIATE_TEST_SUITE_P(MedianTests, TestBinarySearch,
                         testing::Values((TestParams){
                             {1, 0, -1, 0, -2, 2},
                             0,
                             {{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}}}));
