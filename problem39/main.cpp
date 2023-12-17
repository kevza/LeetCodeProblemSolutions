#include <gtest/gtest.h>
#include <vector>
using namespace std;

namespace {
  class Solution {
    public:

      void combinationSumRec(vector<int> nums, int target, int i, vector<int> solution, int sum,  vector<vector<int>>& solutions)
      {
        // Out of numbers
        if (i >= nums.size()) {
          return;
        }
        
        // Valid Solution
        if (sum == target) {
          solutions.push_back(solution);
          return;
        }

        // Number too big
        if (sum > target) {
          return;
        }

        vector<int> newSolution(solution.begin(), solution.end());
        newSolution.push_back(nums[i]);
        combinationSumRec(nums, target, i, newSolution, sum + nums[i], solutions);
        combinationSumRec(nums, target, i + 1, solution, sum, solutions);
      }
      vector<vector<int> > combinationSum(vector<int> nums, int target)
      {
        vector<vector<int> > solution;
        combinationSumRec(nums, target, 0, vector<int>(), 0, solution);
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
  EXPECT_EQ(param.output, s.combinationSum(param.input, param.target));
}


INSTANTIATE_TEST_SUITE_P(LeetcodeSolution, TestSolution, testing::Values((Params){(vector<int>){2,3,6,7}, 7, (vector<vector<int> >){{2,2,3},{7}}}));
