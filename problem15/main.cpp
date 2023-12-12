#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

using namespace std;

class Solution {
public:
  void swap(int &a, int &b) {
    if (a > b) {
      int t = a;
      a = b;
      b = t;
    }
  }

  vector<vector<int>> threeSum(const vector<int> &l) {
    set<vector<int>> result;
    multimap<int, int> index_map;

    for (int i = 0; i < l.size(); i++) {
      if (index_map.count(l[i]) < 3) {
        index_map.insert(pair(l[i], i));
      }
    }
    vector<int> list;
    for (auto &i : index_map) {
      i.second = list.size();
      list.push_back(i.first);
    }

    for (int i = 0; i < list.size(); i++) {
      for (int j = i + 1; j < list.size(); j++) {
        int a = list[i];
        int b = list[j];
        int c = -(a + b);
        auto range = index_map.equal_range(c);
        for (auto it = range.first; it != range.second; it++) {
          if (it->second != i && it->second != j) {
            // Sort
            swap(a, c);
            swap(a, b);
            swap(b, c);
            result.insert({a, b, c});
            break;
          }
        }
      }
    }

    return vector<vector<int>>(result.begin(), result.end());
  }
};

struct TestParams {
  vector<int> input;
  vector<vector<int>> output;
};

class TestBinarySearch : public testing::TestWithParam<TestParams> {};

TEST_P(TestBinarySearch, cases) {
  TestParams p = GetParam();
  Solution s;
  EXPECT_EQ(p.output, s.threeSum(p.input)) << " - Failed";
}

INSTANTIATE_TEST_SUITE_P(
    MedianTests, TestBinarySearch,
    testing::Values((TestParams){vector<int>{-1, 0, 1, 2, -1, -4},
                                 vector<vector<int>>{{-1, -1, 2}, {-1, 0, 1}}},
                    (TestParams){vector<int>{0, 0, 0},
                                 vector<vector<int>>{{0, 0, 0}}},

                    (TestParams){vector<int>{0, -4, -1, -4, -2, -3, 2},
                                 vector<vector<int>>{{-2, 0, 2}}}

                    ));
/*(TestParams){{34, 55,  79, 28,  46, 33,  2,  48,
   31, -3, 84, 71,  52, -3,  93, 15,  21, -43, 57,
   -6, 86, 56,  94, 74,  83, -14, 28, -66, 46, -49,
              62, -11, 43, 65,  77, 12,  47, 61,
   26, 1, 13, 29,  55, -82, 76, 26,  15, -29, 36,
   -29, 10, -70, 69, 17,  49},
             {}}));*/
