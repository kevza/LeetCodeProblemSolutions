#include <climits>
#include <gtest/gtest.h>
#include <iostream>
#include <limits>
#include <math.h>
#include <vector>

using namespace std;

class Solution {
public:
  double findMedianSortedArrays(vector<int> &a, vector<int> &b) {
    if (a.size() > b.size()) {
      return findMedianSortedArrays(b, a);
    }
    int m = a.size();
    int n = b.size();
    int left = 0;
    int right = m;

    while (left <= right) {
      int pA = (left + right) / 2;
      int pB = (m + n + 1) / 2 - pA;
      int maxLeftA = pA - 1 < 0 ? INT_MIN : a[pA - 1];
      int minRightA = pA >= m ? INT_MAX : a[pA];
      int maxLeftB = pB - 1 < 0 ? INT_MIN : b[pB - 1];
      int minRightB = pB >= n ? INT_MAX : b[pB];

      if (maxLeftA > minRightB) {
        right = pA - 1;
      }

      if (maxLeftB > minRightA) {
        left = pA + 1;
      }

      if (maxLeftA <= minRightB && maxLeftB <= minRightA) {
        if ((m + n) % 2 == 0) {
          return (max(maxLeftA, maxLeftB) + min(minRightA, minRightB)) / 2.0;
        } else {
          return max(maxLeftA, maxLeftB);
        }
      }
    }

    return 0;
  }
};

struct TestParams {
  vector<int> nums1;
  vector<int> nums2;
  double result;
};

ostream &operator<<(ostream &os, const TestParams &params) {
  os << "Nums1 : [";
  for (const auto &n : params.nums1) {
    os << n << " ";
  }
  os << "], ";
  os << "Nums2 : [";
  for (const auto &n : params.nums2) {
    os << n << " ";
  }
  os << "]";
  return os;
}

class TestSortedMedian : public testing::TestWithParam<TestParams> {};

TEST_P(TestSortedMedian, cases) {
  TestParams p = GetParam();
  Solution s;
  EXPECT_EQ(p.result, s.findMedianSortedArrays(p.nums1, p.nums2))
      << p << " - Failed";
}

INSTANTIATE_TEST_SUITE_P(
    MedianTests, TestSortedMedian,
    testing::Values((TestParams){{1}, {2, 3}, 2}, (TestParams){{1, 2}, {3}, 2},
                    (TestParams){{1, 3}, {2}, 2}, (TestParams){{1}, {2}, 1.5},
                    (TestParams){{1}, {1}, 1},
                    (TestParams){{1, 2, 3, 4, 5}, {2, 3, 4, 5, 6}, 3.5},
                    (TestParams){{1, 2, 3, 4, 5}, {2, 3, 4, 5}, 3}));
