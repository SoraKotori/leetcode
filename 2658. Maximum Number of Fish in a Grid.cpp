#include "header.h"

class Solution {
public:
    int dfs(vector<vector<int>>& grid, int row, int col)
    {
        int fish = grid[row][col];
        grid[row][col] = 0;

        if (auto i = row - 1; i >= 0            && grid[i][col]) fish += dfs(grid, i, col);
        if (auto i = row + 1; i < size(grid)    && grid[i][col]) fish += dfs(grid, i, col);
        if (auto j = col - 1; j >= 0            && grid[row][j]) fish += dfs(grid, row, j);
        if (auto j = col + 1; j < size(grid[0]) && grid[row][j]) fish += dfs(grid, row, j);
        
        return fish;
    }

    int findMaxFish(vector<vector<int>>& grid) {
        int m = size(grid);
        int n = size(grid[0]);

        int max_fish = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                    max_fish = max(max_fish, dfs(grid, i, j));

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