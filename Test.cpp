#include <algorithm>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

namespace {
using std::min;
using std::numeric_limits;
using std::pair;
using std::queue;
using std::vector;
}

// Time:  O(m * n)
// Space: O(1)

// Two-pass DP solution.
// First pass relaxes from top/left, second pass relaxes from bottom/right.
// Use a finite sentinel to avoid overflow when adding 1.
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        if (matrix.empty()) {
            return matrix;
        }
        const std::size_t cols = matrix[0].size();
        for (const auto& row : matrix) {
            if (row.empty() || row.size() != cols) {
                return matrix;
            }
        }

        const int sentinel = static_cast<int>(matrix.size() + cols);

        for (std::size_t i = 0; i < matrix.size(); ++i) {
            const std::size_t rowSize = matrix[i].size();
            for (std::size_t j = 0; j < rowSize; ++j) {
                if (!matrix[i][j]) {
                    continue;
                }
                matrix[i][j] = sentinel;
                if (i > 0 && matrix[i - 1][j] != sentinel) {
                    matrix[i][j] = min(matrix[i][j], matrix[i - 1][j] + 1);
                }
                if (j > 0 && matrix[i][j - 1] != sentinel) {
                    matrix[i][j] = min(matrix[i][j], matrix[i][j - 1] + 1);
                }
            }
        }

        for (std::size_t i = matrix.size(); i-- > 0;) {
            const std::size_t rowSize = matrix[i].size();
            for (std::size_t j = rowSize; j-- > 0;) {
                if (!matrix[i][j]) {
                    continue;
                }
                if (i < matrix.size() - 1 && matrix[i + 1][j] != sentinel) {
                    matrix[i][j] = min(matrix[i][j], matrix[i + 1][j] + 1);
                }
                if (j < rowSize - 1 && matrix[i][j + 1] != sentinel) {
                    matrix[i][j] = min(matrix[i][j], matrix[i][j + 1] + 1);
                }
            }
        }

        return matrix;
    }
};

// Time:  O(m * n)
// Space: O(m * n)
// dp solution
class Solution2 {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        if (matrix.empty()) {
            return matrix;
        }
        const std::size_t cols = matrix[0].size();
        for (const auto& row : matrix) {
            if (row.empty() || row.size() != cols) {
                return matrix;
            }
        }

        const int sentinel = static_cast<int>(matrix.size() + cols);
        vector<vector<int> > dp(matrix.size(),
                                vector<int>(cols,
                                            sentinel));

        for (std::size_t i = 0; i < matrix.size(); ++i) {
            const std::size_t rowSize = matrix[i].size();
            for (std::size_t j = 0; j < rowSize; ++j) {
                if (matrix[i][j] == 0) {
                    dp[i][j] = 0;
                } else {
                    if (i > 0 && dp[i - 1][j] != sentinel) {
                        dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
                    }
                    if (j > 0 && dp[i][j - 1] != sentinel) {
                        dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
                    }
                }
            }
        }

        for (std::size_t i = matrix.size(); i-- > 0;) {
            const std::size_t rowSize = matrix[i].size();
            for (std::size_t j = rowSize; j-- > 0;) {
                if (matrix[i][j] == 0) {
                    dp[i][j] = 0;
                } else {
                    if (i < matrix.size() - 1 && dp[i + 1][j] != sentinel) {
                        dp[i][j] = min(dp[i][j], dp[i + 1][j] + 1);
                    }
                    if (j < rowSize - 1 && dp[i][j + 1] != sentinel) {
                        dp[i][j] = min(dp[i][j], dp[i][j + 1] + 1);
                    }
                }
            }
        }

        return dp;
    }
};

// Time:  O(m * n)
// Space: O(m * n)
class Solution3 {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        queue<pair<int, int>> queue;
        const std::size_t rows = matrix.size();
        const std::size_t cols = rows ? matrix[0].size() : 0;
        for (const auto& row : matrix) {
            if (row.empty() || row.size() != cols) {
                return matrix;
            }
        }
        for (std::size_t i = 0; i < rows; ++i) {
            for (std::size_t j = 0; j < cols; ++j) {
                if (matrix[i][j] == 0) {
                    queue.emplace(static_cast<int>(i), static_cast<int>(j));
                }
                else {
                    matrix[i][j] = numeric_limits<int>::max();
                }
            }
        }

        const vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        while (!queue.empty()) {
            auto cell = queue.front();
            queue.pop();
            for (const auto& dir : dirs) {
                auto i = cell.first + dir.first;
                auto j = cell.second + dir.second;
                if (!(0 <= i && static_cast<std::size_t>(i) < rows && 0 <= j && static_cast<std::size_t>(j) < cols && 
                      matrix[i][j] > matrix[cell.first][cell.second] + 1)) {
                        continue;
                }
                queue.emplace(i, j);
                matrix[i][j] = matrix[cell.first][cell.second] + 1;
            }
        }
        
        return matrix;
    }
};
