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
        const size_t rowCount = matrix.size();
        const size_t colCount = matrix[0].size();
        for (const auto& row : matrix) {
            if (row.size() != colCount || row.empty()) {
                return matrix;
            }
        }

        const int sentinel = static_cast<int>(rowCount + colCount);

        for (size_t i = 0; i < rowCount; ++i) {
            const size_t rowSize = matrix[i].size();
            for (size_t j = 0; j < rowSize; ++j) {
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

        for (size_t i = rowCount; i-- > 0;) {
            const size_t rowSize = matrix[i].size();
            for (size_t j = rowSize; j-- > 0;) {
                if (!matrix[i][j]) {
                    continue;
                }
                if (i + 1 < rowCount && matrix[i + 1][j] != sentinel) {
                    matrix[i][j] = min(matrix[i][j], matrix[i + 1][j] + 1);
                }
                if (j + 1 < rowSize && matrix[i][j + 1] != sentinel) {
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
        const size_t rowCount = matrix.size();
        const size_t colCount = matrix[0].size();
        for (const auto& row : matrix) {
            if (row.size() != colCount || row.empty()) {
                return matrix;
            }
        }

        const int sentinel = static_cast<int>(rowCount + colCount);
        vector<vector<int> > dp(rowCount,
                                vector<int>(colCount,
                                            sentinel));

        for (size_t i = 0; i < rowCount; ++i) {
            const size_t rowSize = matrix[i].size();
            for (size_t j = 0; j < rowSize; ++j) {
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

        for (size_t i = rowCount; i-- > 0;) {
            const size_t rowSize = matrix[i].size();
            for (size_t j = rowSize; j-- > 0;) {
                if (matrix[i][j] == 0) {
                    dp[i][j] = 0;
                } else {
                    if (i + 1 < rowCount && dp[i + 1][j] != sentinel) {
                        dp[i][j] = min(dp[i][j], dp[i + 1][j] + 1);
                    }
                    if (j + 1 < rowSize && dp[i][j + 1] != sentinel) {
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
        queue<pair<size_t, size_t>> queue;
        if (matrix.empty()) {
            return matrix;
        }
        const size_t rowCount = matrix.size();
        const size_t colCount = matrix[0].size();
        for (const auto& row : matrix) {
            if (row.size() != colCount || row.empty()) {
                return matrix;
            }
        }
        for (size_t i = 0; i < rowCount; ++i) {
            for (size_t j = 0; j < colCount; ++j) {
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
                const long long i = static_cast<long long>(cell.first) + dir.first;
                const long long j = static_cast<long long>(cell.second) + dir.second;
                if (!(0 <= i && i < static_cast<long long>(rowCount) && 0 <= j && j < static_cast<long long>(colCount) &&
                      matrix[static_cast<size_t>(i)][static_cast<size_t>(j)] > matrix[cell.first][cell.second] + 1)) {
                        continue;
                }
                queue.emplace(static_cast<size_t>(i), static_cast<size_t>(j));
                matrix[static_cast<size_t>(i)][static_cast<size_t>(j)] = matrix[cell.first][cell.second] + 1;
            }
        }
        
        return matrix;
    }
};
