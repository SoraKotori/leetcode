#include "header.h"

class Solution {
    array<pair<int, int>, 4> dirs{{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};
public:
    int dfs(vector<vector<int>>& grid, int row, int col)
    {
        int m = size(grid);
        int n = size(grid[0]);

        int fish = grid[row][col];
        grid[row][col] = 0;
        for (auto [dir_i, dir_j] : dirs)
        {
            auto i = row + dir_i;
            auto j = col + dir_j;

            if (0 <= i && 0 <= j && i < m && j < n &&
                grid[i][j] > 0)
            {
                fish += dfs(grid, i, j);
            }
        }

        return fish;
    }

    int findMaxFish(vector<vector<int>>& grid) {
        int m = size(grid);
        int n = size(grid[0]);

        int max_fish = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] > 0)
                {
                    max_fish = max(max_fish, dfs(grid, i, j));
                }

        return max_fish;
    }
};

int main() {
    vector<vector<int>> grid = {
        {0, 2, 1, 0},
        {4, 0, 0, 3},
        {1, 0, 0, 4},
        {0, 3, 2, 0}
    };

    Solution solution;
    int result = solution.findMaxFish(grid);

    cout << "Maximum number of fish: " << result << endl;

    return 0;
}