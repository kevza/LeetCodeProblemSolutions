#include <algorithm>
#include <gtest/gtest.h>
#include <vector>
using namespace std;

namespace {
  class Solution {
    public:
      int binarySearch(vector<int>&nums, int first, int last, int target) {
        while (first < last) {
          int i = first + (last - first) / 2;

          if (nums[i] < target) {
            first = i + 1;
          }
          else if (nums[i] > target) {
            last = i;
          } else {
            return i; 
          }
        }
        if (first == last && first < nums.size() && nums[first] == target) return first;
        return -1;
      }

      vector<int> searchRange(vector<int>& nums, int target) {
        int left_min = 0;
        int left_max = nums.size();
        int right_min = 0;
        int right_max = nums.size();
        int i = binarySearch(nums, left_min, left_max, target);
        if (i == -1) return {-1, -1};
        
        left_max = i;
        right_min = i;
        while (left_min < left_max) {
          int i = binarySearch(nums, left_min, left_max - 1, target);
          if (i == -1) {
            break;
          } else {
            left_max = i;
          }
        }
        while (right_min < right_max) {
          int i = binarySearch(nums, right_min + 1, right_max, target);
          if (i == -1) {
            break; 
          } else{
            right_min = i;
          }
        }
        return {left_max, right_min};
      }
  };
}

struct Params {
  vector<int> input;
  int target;
  vector<int> output;
};

class TestSolution : public testing::TestWithParam<Params> {
};

TEST_P(TestSolution, Test) {
  auto param = GetParam();
  auto s = Solution();
  EXPECT_EQ(param.output, s.searchRange(param.input, param.target));
}


INSTANTIATE_TEST_SUITE_P(LeetcodeSolution, TestSolution,
                         testing::Values((Params){{5,7,7,8,8,10}, 8, {3,4}},
                                          (Params){{5,7,7,8,8,10}, 6, {-1,-1}},
                                          (Params){{}, 6, {-1,-1}},
                                          (Params){{2,2}, 2, {0, 1}},
                                          (Params){{1, 2,2}, 2, {1, 2}},
                                          (Params){{1,1,2}, 1, {0, 1}}
                                         ));
