#include <gtest/gtest.h>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

namespace {
  class Solution {
    public:

      void combinationSumRec(vector<pair<int, int> >& nums, int target, int i, vector<int> &solution, int sum,  vector<vector<int> >& solutions)
      {
        
        // Valid Solution
        if (sum == target) {
          solutions.push_back(solution);
          return;
        }

        // Out of numbers
        if (i >= nums.size()) {
          return;
        }

        // Number too big
        if (sum > target) {
          return;
        }

        int digit = nums[i].first;
        int count = nums[i].second;

        for (int j = 0; j < count; j++)
        {
          solution.push_back(digit);
          sum += digit;
          if (sum <= target)
          {
            combinationSumRec(nums, target, i + 1, solution, sum, solutions);
          }
        }

        for (int j = 0; j < nums[i].second; j++)
        {
          sum -= digit;
          solution.pop_back();
        }

        combinationSumRec(nums, target, i + 1, solution, sum, solutions);
      }

      vector<vector<int> > combinationSum2(vector<int> nums, int target)
      {
        vector<vector<int> > solution;
        map<int, int> frequencyMap;
        for (auto num : nums) {
          frequencyMap[num] += 1;
        }
        vector<pair<int, int> > input(frequencyMap.begin(), frequencyMap.end());

        vector<int> s;
        combinationSumRec(input, target, 0, s, 0, solution);
        return solution;
      }
  };
}

struct Params {
  vector<int> input;
  int target;
  vector<vector<int> > output;
};

class TestSolution : public testing::TestWithParam<Params> {
};

TEST_P(TestSolution, Test) {
  auto param = GetParam();
  auto s = Solution();
  EXPECT_EQ(param.output, s.combinationSum2(param.input, param.target));
}


INSTANTIATE_TEST_SUITE_P(LeetcodeSolution, TestSolution, testing::Values((Params){(vector<int>){10,1,2,7,6,1,5}, 8, (vector<vector<int> >){{1,1,6},{1,2,5},{1,7},{2,6}}}));
