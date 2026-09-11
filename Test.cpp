#include <algorithm>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

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
        for (const auto& row : matrix) {
            if (row.empty()) {
                return matrix;
            }
        }

        const int sentinel = static_cast<int>(matrix.size() + matrix[0].size());

        for (int i = 0; i < matrix.size(); ++i) {
            const int rowSize = static_cast<int>(matrix[i].size());
            for (int j = 0; j < rowSize; ++j) {
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

        for (int i = matrix.size() - 1; i >= 0; --i) {
            const int rowSize = static_cast<int>(matrix[i].size());
            for (int j = rowSize - 1; j >= 0; --j) {
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
        for (const auto& row : matrix) {
            if (row.empty()) {
                return matrix;
            }
        }

        const int sentinel = static_cast<int>(matrix.size() + matrix[0].size());
        vector<vector<int> > dp(matrix.size(),
                                vector<int>(matrix[0].size(),
                                            sentinel));

        for (int i = 0; i < matrix.size(); ++i) {
            const int rowSize = static_cast<int>(matrix[i].size());
            for (int j = 0; j < rowSize; ++j) {
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

        for (int i = matrix.size() - 1; i >= 0; --i) {
            const int rowSize = static_cast<int>(matrix[i].size());
            for (int j = rowSize - 1; j >= 0; --j) {
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
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                if (matrix[i][j] == 0) {
                    queue.emplace(i, j);
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
                if (!(0 <= i && i < matrix.size() && 0 <= j && j < matrix[0].size() && 
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
