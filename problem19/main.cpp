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
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    auto _p = make_unique<ListNode>(0, head);
    ListNode *p = _p.get();

    vector<ListNode *> indexed(31, nullptr);
    int count = 0;
    while (p) {
      indexed[count++] = p;
      p = p->next;
    }

    int i = count - n;
    ListNode *tmp = indexed[i];
    indexed[i - 1]->next = tmp->next;
    delete tmp;

    return _p->next;
  };
};

struct TestParams {
  vector<int> input;
  int target;
  vector<int> output;
};

class TestBinarySearch : public testing::TestWithParam<TestParams> {};

TEST_P(TestBinarySearch, cases) {
  TestParams p = GetParam();
  Solution s;

  ListNode *input = listFromVec(p.input);
  ListNode *output = s.removeNthFromEnd(input, p.target);
  vector<int> result = vecFromList(output);
  EXPECT_EQ(p.output, result) << " - Failed";
  freeList(output);
}

INSTANTIATE_TEST_SUITE_P(MedianTests, TestBinarySearch,
                         testing::Values((TestParams){{1}, 1, {}},
                                         (TestParams){{1, 2, 3}, 1, {1, 2}},
                                         (TestParams){{1, 2, 3}, 2, {1, 3}},
                                         (TestParams){{1, 2, 3}, 3, {2, 3}}));
