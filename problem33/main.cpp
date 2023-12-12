#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

class Solution {
public:
  int search(vector<int> &nums, int target) {
    int n = nums.size();
    int pivot = 0;
    int a = 0;
    int b = n - 1;
    int steps = 0;
    // Find the Pivot
    while (pivot < b) {
      steps++;
      int c = (pivot + b) >> 1;
      if (nums[c] > nums[b]) {
        pivot = c + 1;
      } else {
        b = c;
      }
    }

    b = n;
    if (n > 0 && nums[0] <= target) {
      b = pivot ? pivot : n;
    } else {
      a = pivot;
    }

    while (a < b) {
      steps++;
      int i = (a + b) >> 1;
      int item = nums[i];
      if (item < target) {
        a = i + 1;
      } else if (item > target) {
        b = i;
      } else {
        cout << steps << endl;
        return i;
      }
    }

    return -1;
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
  EXPECT_EQ(p.output, s.search(p.input, p.target)) << " - Failed";
}

INSTANTIATE_TEST_SUITE_P(
    MedianTests, TestBinarySearch,
    testing::Values((TestParams){{0, 1, 2, 3, 4, 5}, 2, 2},
                    (TestParams){{3, 4, 5, 0, 2, 3}, 2, 4},
                    (TestParams){{4, 5, 6, 7, 0, 1, 2}, 3, -1},
                    (TestParams){{}, 0, -1}, (TestParams){{1}, 0, -1},
                    (TestParams){{3, 1}, 3, 0},
                    (TestParams){{4, 5, 6, 7, 0, 1, 2}, 0, 4}));
