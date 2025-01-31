#include "header.h"

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        auto m = size(grid);
        auto n = size(grid[0]);

        vector<int> parents(m * n);
        ranges::iota(parents, 0);

        auto find_root = [&](auto node)
        {
            for (int root; (root = parents[node]) != node; node = root);
            return node;
        };

        int max_island = 0;
        vector<int> island_size(m * n);
        for (int i = 0 ; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                {
                    island_size[i * n + j] = 1;
                    max_island = 1;
                }

        array<pair<int, int>, 4> dirs{{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};
        for (int i = 0 ; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                {
                    auto node_0 = i * n + j;
                    auto root_0 = find_root(node_0);

                    for (auto [dir_i, dir_j] : dirs)
                    {
                        auto row = i + dir_i;
                        auto col = j + dir_j;

                        if (0 <= row && 0 <= col && row < m && col < n && grid[row][col])
                        {
                            auto node_1 = row * n + col;
                            auto root_1 = find_root(node_1);

                            if (root_0 == root_1)
                                continue;

                            if (node_0 != root_0 || node_1 == root_1)
                            {
                                parents[root_1] = root_0;
                                island_size[root_0] += island_size[root_1];
                                island_size[root_1] = 0;
                                max_island = max(max_island, island_size[root_0]);
                            }
                            else
                            {
                                parents[root_0] = root_1;
                                island_size[root_1] += island_size[root_0];
                                island_size[root_0] = 0;
                                max_island = max(max_island, island_size[root_1]);
                            }
                        }
                    }
                }

        for (int i = 0 ; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 0)
                {
                    int island = 1;
                    set<int> island_root;

                    for (int dir_i = 0; dir_i < 4; dir_i++)
                    {
                        auto node_0_i = i + dirs[dir_i].first;
                        auto node_0_j = j + dirs[dir_i].second;

                        if (node_0_i < 0 || node_0_j < 0 || m <= node_0_i || n <= node_0_j ||
                            grid[node_0_i][node_0_j] == 0)
                            continue;
                        auto node_0 = node_0_i * n + node_0_j;
                        auto root_0 = find_root(node_0);

                        if (!island_root.contains(root_0))
                        {
                            island_root.emplace(root_0);
                            island += island_size[root_0];
                        }
                    }

                    max_island = max(max_island, island);
                }

        return max_island;
    }
};

int main() {
    Solution solution;

    // Additional Test Case
    vector<vector<int>> grid0 = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 0},
        {1, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 0},
        {0, 1, 1, 1, 1, 0, 0}
    };
    int result0 = solution.largestIsland(grid0);
    cout << "Additional Test Case Output: " << result0 << endl;

    // Example 1
    vector<vector<int>> grid1 = {{1, 0}, {0, 1}};
    int result1 = solution.largestIsland(grid1);
    cout << "Example 1 Output: " << result1 << endl;

    // Example 2
    vector<vector<int>> grid2 = {{1, 1}, {1, 0}};
    int result2 = solution.largestIsland(grid2);
    cout << "Example 2 Output: " << result2 << endl;

    // Example 3
    vector<vector<int>> grid3 = {{1, 1}, {1, 1}};
    int result3 = solution.largestIsland(grid3);
    cout << "Example 3 Output: " << result3 << endl;

    // Example 4
    vector<vector<int>> grid4 = {{1}};
    int result4 = solution.largestIsland(grid4);
    cout << "Example 4 Output: " << result4 << endl;

    return 0;
}