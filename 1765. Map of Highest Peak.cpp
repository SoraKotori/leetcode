#include "header.h"

class Solution_BFS {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        auto m = size(isWater);
        auto n = size(isWater[0]);

        queue<pair<int, int>> queue;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (isWater[i][j])
                {
                    queue.emplace(i, j);
                    isWater[i][j] = 0;
                }
                else
                    isWater[i][j] = numeric_limits<int>::max();

        array<pair<int, int>, 4> dirs{{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}};
        while (!queue.empty())
        {
            auto [row, col] = queue.front();
            queue.pop();

            for (auto [dir_i, dir_j] : dirs)
            {
                auto i = row + dir_i;
                auto j = col + dir_j;
                if (i < 0 || j < 0 || i == m || j == n ||
                    isWater[i][j] <= isWater[row][col] + 1)
                    continue;

                isWater[i][j] = isWater[row][col] + 1;
                queue.emplace(i, j);
            }
        }

        return isWater;
    }
};

class Solution_DP {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        auto m = size(isWater);
        auto n = size(isWater[0]);

        isWater[0][0] = isWater[0][0] ? 0 : numeric_limits<int>::max() - m - n;
        for (int i = 1; i < m; i++)
            isWater[i][0] = isWater[i][0] ? 0 : isWater[i - 1][0] + 1;

        for (int j = 1; j < n; j++)
            isWater[0][j] = isWater[0][j] ? 0 : isWater[0][j - 1] + 1;

        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                isWater[i][j] = isWater[i][j] ? 0 : min(isWater[i - 1][j], isWater[i][j - 1]) + 1;

        for (int i = m - 2; i >= 0; i--)
            isWater[i][n - 1] = min(isWater[i][n - 1], isWater[i + 1][n - 1] + 1);
        
        for (int j = n - 2; j >= 0; j--)
            isWater[m - 1][j] = min(isWater[m - 1][j], isWater[m - 1][j + 1] + 1);

        for (int i = m - 2; i >= 0; i--)
            for (int j = n - 2; j >= 0; j--)
                isWater[i][j] = min(isWater[i][j], min(isWater[i + 1][j], isWater[i][j + 1]) + 1);

        return isWater;
    }
};

int main() {
    Solution_DP solution;
    vector<vector<int>> isWater1 = {{0, 1}, {0, 0}};
    vector<vector<int>> isWater2 = {{0, 0, 1}, {1, 0, 0}, {0, 0, 0}};

    vector<vector<int>> result1 = solution.highestPeak(isWater1);
    vector<vector<int>> result2 = solution.highestPeak(isWater2);

    cout << "Result 1:" << endl;
    for (const auto& row : result1) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }

    cout << "Result 2:" << endl;
    for (const auto& row : result2) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }

    return 0;
}