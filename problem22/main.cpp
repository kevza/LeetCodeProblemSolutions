#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

vector<int> vecFromList(ListNode *head) {
  vector<int> r;
  ListNode *p = head;
  while (p) {
    r.push_back(p->val);
    p = p->next;
  }
  return r;
}

ListNode *listFromVec(const vector<int> &l) {
  ListNode *p = nullptr;
  ListNode *r = nullptr;
  for (auto v : l) {
    if (p) {
      p->next = new ListNode(v);
      p = p->next;
    } else {
      p = new ListNode(v);
      r = p;
    }
  }
  return r;
}

void freeList(ListNode *p) {
  while (p) {
    ListNode *next = p->next;
    delete p;
    p = next;
  }
}

class Solution {
public:
  ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
    auto sorted = make_unique<ListNode>();
    ListNode *p = sorted.get();
    ListNode *p1 = list1;
    ListNode *p2 = list2;
    while (p1 != nullptr && p2 != nullptr) {
      if (p1->val <= p2->val) {
        p->next = p1;
        p = p1;
        p1 = p1->next;
      } else {
        p->next = p2;
        p = p2;
        p2 = p2->next;
      }
    }
    if (p2 != nullptr) {
      p1 = p2;
    }
    while (p1 != nullptr) {
      p->next = p1;
      p = p1;
      p1 = p1->next;
    }

    return sorted->next;
  }

  ListNode *mergeKLists(vector<ListNode *> &lists) {
    int n = lists.size();
    if (n == 0)
      return nullptr;
    if (n % 2 == 1) {
      n++;
      lists.push_back(nullptr);
    }
    int l = 1;
    int k = 2;
    while (l < n) {
      for (int i = 0; i + l < n; i += k) {
        cout << i << ":" << i + l << endl;
        ListNode *l1 = lists[i];
        ListNode *l2 = lists[i + l];
        lists[i] = mergeTwoLists(l1, l2);
      }
      l = l << 1;
      k = k << 1;
    }

    return lists[0];
  }
};

struct TestParams {
  vector<ListNode *> input;
  vector<int> output;
};

class TestBinarySearch : public testing::TestWithParam<TestParams> {};

TEST_P(TestBinarySearch, cases) {
  TestParams p = GetParam();
  Solution s;
  ListNode *output = s.mergeKLists(p.input);
  vector<int> result = vecFromList(output);
  EXPECT_EQ(p.output, result) << " - Failed";
  freeList(output);
}

INSTANTIATE_TEST_SUITE_P(
    MedianTests, TestBinarySearch,
    testing::Values((TestParams){{listFromVec({1, 4, 5}),
                                  listFromVec({1, 3, 4}), listFromVec({2, 6})},
                                 {1, 1, 2, 3, 4, 4, 5, 6}},
                    (TestParams){{listFromVec({}), listFromVec({-1, 5}),
                                  listFromVec({1, 4, 6}),
                                  listFromVec({4, 5, 6})},
                                 {-1, 1, 4, 4, 5, 5, 6, 6}},
                    (TestParams){{}, {}}, (TestParams){{listFromVec({})}, {}},
                    (TestParams){{listFromVec({}), listFromVec({1})}, {1}}));
