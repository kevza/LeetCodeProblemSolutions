#include <gtest/gtest.h>
#include <vector>
using namespace std;

namespace {
class Solution {
public:
  bool notAClash(int c, int r, char t, const vector<vector<char>> &board) {
    // Check Column and Check Row
    for (int y = 0; y < 9; y++) {
      if (board[y][c] == t) {
        return false;
      }

      if (board[r][y] == t) {
        return false;
      }
    }

    // Check Square
    r = (r / 3) * 3;
    c = (c / 3) * 3;
    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 3; y++) {
        if (board[r + y][c + x] == t) {
          return false;
        }
      }
    }

    return true;
  }
  bool isValidSudoku(vector<vector<char>> &board) {
    for (int r = 0; r < 9; r++) {
      for (int c = 0; c < 9; c++) {
        char t = board[r][c];
        if (t != '.') {
          board[r][c] = '.';
          if (!notAClash(c, r, t, board)) {
            return false;
          }
          board[r][c] = t;
        }
      }
    }
    return true;
  }
};
} // namespace

struct Params {
  vector<vector<char>> input;
  bool output;
};

class TestSolution : public testing::TestWithParam<Params> {};

TEST_P(TestSolution, Test) {
  auto param = GetParam();
  auto s = Solution();
  EXPECT_EQ(param.output, s.isValidSudoku(param.input));
}

INSTANTIATE_TEST_SUITE_P(LeetcodeSolution, TestSolution,
                         testing::Values((Params){
                             {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                              {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                              {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                              {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                              {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                              {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                              {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                              {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                              {'.', '.', '.', '.', '8', '.', '.', '7', '9'}},
                             true}));
